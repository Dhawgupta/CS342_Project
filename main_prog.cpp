#include "Layer2.h"
#include "Layer1.h"
#include "Layer0.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <iostream>

using namespace std;
string s[10],line;
map<string,int> mp,instr;
inode_struct v[100],node;
bool mark[100],data[100];
/*************************************************/
void print(){
	cout<<"Inode Details :-\n";
	cout<<"Inode block : "<<(node.inode)<<endl;
	cout<<"Inode Permission : "<<(node.permission)<<endl;
	cout<<"Links :"<<(node.nlinks)<<endl;
	cout<<"Block Size :"<<(node.block_size)<<endl;
	cout<<"Number of Blocks :"<<(node.blocks)<<endl;
	cout<<"Data Block Addresses : ";
	for(int i=0;i<5;i++){
		if((node.direct_p[i])==NULL)
			break;
		else
			cout<<(node.direct_p[i])<<",";
	}cout<<endl;
	cout<<"Creation Time :"<<(node.created)<<endl;
	cout<<"Modified Time :"<<(node.modified)<<endl;
}

/*************************************************/
int main(int argc, char const *argv[]){
	instr["create"]=1;
	instr["open"]=2;
	instr["close"]=3;
	instr["append"]=4;
	instr["read"]=5;
	instr["write"]=6;
	instr["viewInode"]=7;
	instr["delete"]=8;
	instr["exit"]=9;
	void* mm = allocate_memory_block(64);
	superblock sb(mm);
	while(1){
		cout<<"Enter the command:"<<endl;
		getline(cin,line);
		int len=0,last=0;
		for(int i=0;i<(int)line.size();i++){
			if(line[i]==' '){
				s[len]=line.substr(last,i-last);
				len++;
				last=i;
			}
		}
		cout<<endl;
		s[len]=line.substr(last,(int)line.size()-last);
		if(instr.find(s[0])==instr.end()){
			cout<<"Command not found!!\n";
			continue;
		}

		switch(instr[s[0]]){
			case 1: if(len==1)s[1]="untitled";
					if(mp.find(s[1])!=mp.end()){
						cout<<"Default file already exists";
					}
					else{
						int pos=createfile(mm,s[1]);
						if(pos!=-1){
							mp[s[1]]=pos;
							cout<<"File successfully added";
						}
						else{
							cout<<"File couldn't be added";
						}
					}
					break;
			case 2: if(len==1)s[1]="untitled";
					if(mp.find(s[1])==mp.end()){
						cout<<"File doesn't exists";
					}
					else{
						node=fileopen(mm,mp[s[1]]);
						if(!mark[mp[s[1]]]){
							v[mp[s[1]]]=node;
							cout<<"File successfully opened.\n";
							cout<<"File table entry cached.\n";
							print();
							mark[mp[s[1]]]=true;
						}
						else
							cout<<"File already opened";	
					}
					break;
			case 3: if(len==1)s[1]="untitled";
					if(mp.find(s[1])==mp.end())
						cout<<"File doesn't exists";
					else{
						if(!mark[mp[s[1]]])
							cout<<"File is not opened";
						else{
							cout<<"File is closed now";
							mark[mp[s[1]]]=false;
						}
					}
					break;
			case 4: {
						if(len==1)s[1]="untitled";
						if(mp.find(s[1])==mp.end()){
							cout<<"File doesn't exists.";
							break;
						}
						if(!mark[mp[s[1]]]){
							cout<<"ERROR:File not opened.";
							break;
						}
						cout<<"Enter the data(terminate by printing '.') :-\n";
						getline(cin,line,'.');
						if(data[mp[s[1]]]){
							char *temp_s=(char *)v[mp[s[1]]].direct_p[0];
							while(temp_s[0]!='\0')
								temp_s++;
							strcpy(temp_s,line.c_str());
						}
						else{
							strcpy((char *)v[mp[s[1]]].direct_p[0],line.c_str());
							data[mp[s[1]]]=1;	
						}
						time_t tt=time(0);
						v[mp[s[1]]].modified=tt;
						v[mp[s[1]]].written=tt;
						inode_manager::inode_write(mm,v[mp[s[1]]]);
						break;
					}	
			case 5: {
						if(len==1)s[1]="untitled";
						if(mp.find(s[1])==mp.end()){
							cout<<"File doesn't exists.";
							break;
						}
						if(!mark[mp[s[1]]]){
							cout<<"ERROR:File not opened.";
							break;
						}
						if(!data[mp[s[1]]]){
							break;
						}
						char *temp_s=(char *)v[mp[s[1]]].direct_p[0];
						for(int i=0;temp_s[i]!='\0';i++)
							cout<<temp_s[i];
						break;
					}
			case 6:	if(len==1)s[1]="untitled";
					if(mp.find(s[1])==mp.end()){
							cout<<"File doesn't exists.";
							break;
						}
					if(!mark[mp[s[1]]]){
						cout<<"ERROR:File not opened.";
						break;
					}
					cout<<"Enter the data(terminate by printing '.') :-\n";
					getline(cin,line,'.');
					strcpy((char *)v[mp[s[1]]].direct_p[0],line.c_str());
					data[mp[s[1]]]=1;
					v[mp[s[1]]].modified=time(0);
					v[mp[s[1]]].written=time(0);
					inode_manager::inode_write(mm,v[mp[s[1]]]);
					break;
			case 7: if(len==1)s[1]="untitled";
					if(mp.find(s[1])==mp.end()){
						cout<<"File doesn't exists.";
						break;
					}
					if(!mark[mp[s[1]]]){
						cout<<"ERROR:File not opened.";
						break;
					}
					node=v[mp[s[1]]];
					print();
					break;
			case 8:	if(len==1)s[1]="untitled";
					if(mp.find(s[1])==mp.end()){
						cout<<"File doesn't exists.";
						break;
					}
					if(mark[mp[s[1]]]){
						cout<<"File is currently opened.Close it first.";
						break;
					}
					mark[mp[s[1]]]=0;
					data[mp[s[1]]]=0;
					delete_file(mm,mp[s[1]]);
					mp.erase(s[1]);
					cout<<"File successfully deleted.";
					break;
			case 9: cout<<"Exiting........";
					break;
			default:cout<<"Wrong Command";
		}
		cout<<endl<<endl;
		if(instr[s[0]]==9)break;
	}
	free(mm);
	return 0;
}