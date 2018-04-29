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
bool mark[100];
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
	instr["write"]=4;
	instr["exit"]=5;
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
			cout<<"Command not found!!";
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
			case 4: if(len==1)s[1]="untitled";
					if(!mark[mp[s[1]]]){
						cout<<"ERROR:File not opened.";
						break;
					}
					cout<<"Enter the data(terminate by printing -1) :-\n";
					getline(cin,line,'.');
					strcpy((char *)v[mp[s[1]]].direct_p[0],line.c_str());
					break;
			case 5: cout<<"Exiting........";
					break;
			default:cout<<"Wrong Command";
		}
		cout<<endl;
		if(instr[s[0]]==5)break;
	}
	free(mm);
	return 0;
}