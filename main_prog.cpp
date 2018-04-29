#include "Layer2.h"
#include "Layer1.h"
#include "Layer0.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string>
#include <string.h>

using namespace std;
string s[10];
map<string,int> mp,instr;
inode_struct *a[100];
int main(int argc, char const *argv[]){
	instr["create"]=1;
	instr["open"]=2;
	instr["close"]=3;
	void* mm = allocate_memory_block(64);
	superblock(mm);
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
						pos=createfile(mm,s[1]);
						if(pos!=-1){
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
						inode_struct *node=fileopen(s[1]);
						if(node!=NULL)
							v[mp[s[1]]]=node;
						else
							cout<<"Couldn't open file";	
					}
					break;
			case 3: if(len==1)s[1]="untitled";
					if(mp.find(s[1])==mp.end())
						cout<<"File doesn't exists";
					else{
						if(v[mp[s[1]]]==NULL)
							cout<<"File is not opened";
						else{
							cout<<"File is closed now";
							v[mp[s[1]]]=NULL:
						}
					}
					break;
			default:cout<<"Wrong Command";
		}
		cout<<endl;
	}

	return 0;
}