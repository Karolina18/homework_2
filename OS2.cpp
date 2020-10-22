#include <iostream>
#include <cerrno>
#include <unistd.h>

#define BUFF_SIZE 1024

int copy1(int sourse_OP,int destination_OP,data){
	
	char buffer[BUFF_SIZE];
	
	int read_sourse=read(sours_OP,buffer,data);
	
	if(read_sourse==-1){
		
		std:cout<<"somethihg went wrong while reading the file.Error"<strerror(errno);
		exit(errno);
	}
	if(read_sourse==0){
		
		return;
	}
	int write_dest=write(destination_OP,buffer,read_sourse);
	
	if(write_dest==-1){
		
		std:cout<<"somethihg went wrong while writing the file.Error"<strerror(errno);
		
		exit(errno);
	}
return write_dest;
}
	
	
	
int copy_file(int sourse_OP,int destination_OP,int sourse_logical_size){
	
	int sourse_physical_size=0;
	
    int destination_physical_size=0;
    
//move to the beginning of the file
	int begin_sourse = lseek(sourse_OP,0,SEEK_SET);
	
	if(begin_sorse == -1){
		
		return -1;
	}
	
//hole_begin start byte
	int check=lseek(sourse_OP,0,SEEK_HOLE);
	
	if(check == -1){
		
		return -1;
	}
	
//if the beginning of the file is a hole
	if(check == begin_sourse){
		
		int hole_end = lseek(sourse_OP,0,SEEK_DATA);
		
		//if the file is a hole
		if(hole_end == -1){
			
			if(errno == ENXIO){
			
				lseek(destination_OP,sourse_logical_size,SEEK_SET)
			}
			return 0;
		}
		
		hole_size=hole_end-check;
		
		//copy hole in destination_OP
		int begin_dest =lseek(destination_OP,hole_size,SEEK_SET);
		
		if(begin_dest == -1){
			
			return -1;
		}
	}
	
	while(1){
		//finding data without holes
		int location = lseek(sourse_OP, 0, SEEK_CUR);
		
		if(location == -1){
			
				return -1;
		}
		int hole_begin= lseek(sourse_OP, 0, SEEK_HOLE);
		
		//if there are not holes
		if(hole_begin == -1 || hole_begin == sourse_logical_size){
			
			int byte_end=lseek(sourse_OP,0,SEEK_END);
			
			//move the pointer to copy from the desired data area
			
			lseek(sourse_OP,location,SEEK_SET)
			
			sourse_physical_size+=byte_end;
			
			destination_physical_size+=copy1(sourse_OP,destination_OP,byte_end);
			
		 return 0;
		}
		lseek(sourse_OP,hole_begin,SEEK_SET);
		
		//data size
		
		int data=hole_begin-location;
		
		//copy data
		if(data){
			
			//move the pointer to copy from the desired data area
			lseek(sourse_OP,location,SEEK_SET);
			
			sourse_physical_size+=data;
			
			destination_physical_size+=copy1(sourse_OP,destination_OP,data);
		}
		//make hole (destination_OP)
		
		 hole_end=lseek(sourse_OP,0,SEEK_DATA);
		 
		 //if the end of the file is a hole
		 if(hole_end==-1){
		 	
		 	if(errno==ENXIO){
		 		
		 		int last_hole=sourse_logical_size-hole_begin;
		 		
		 		lseek(destination_OP, last_hole ,SEEK_CUR);
		 		
		 		return 0;
		 	}
		 }
		 
		 hole_size=hole_end-hole_begin;
		 
		lseek(destination_OP,hole_size,SEEK_CUR);
	}
	std::cout<<"physical size of the sourse is"<<sourse_physical_size;
	
	std::cout<<"physical size of the destination is"<<destination_physical_size;
}


int main(int argc,char** argv){
	
	if(argc<3){
		
		std::cout<<"not enough arguments to copy";
		
		exit(1);
	}
	//
	const char* sourse=argv[1];
	
	//open sourse
	int sourse_OP=open(sourse,O_RDONLY);
	
	if(sourse_OP==-1){
		
		std::cout<<"cant open file";
		
		return -1;
	}
	int sourse_logical_size=lseek(sorse_OP,0,SEEK_END);
	
	std::cout<<"logical size of the sourse is"<<sourse_logical_size;
	
	const char* destination=argv[2];
	
	int destination_OP=open(destination,O_WRONLY|O_TRUNC|O_CREAT,S_IRUSR|S_IWUSR|S_RGRP);
	
	if(destination_OP==-1){
		
		std::cout<<"cant open file";
		
		return -1;
	}
	
	int sourse_physical_size=0;
	
	
	copy_file(sourse_OP,destination_OP,sourse_logical_size);
	
	lseek(destination_OP,0,SEEK_SET);
	
	int destination_logical_size=lseek(destination_OP,0,SEEK_END);
	
	std::cout<<"logical size of the destination is "<<destination_logical_size;
	
	close(sourse);
	
	close(destination);
	
}
