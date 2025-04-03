#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//create fucnctions 4 functions
void print(char *);
void mostpackages();
void packageTranfer(char *,char *,int,int);
void freeMemory(); 

//Package structure
typedef struct packages{
    char id[100];                //Package id 
    int weight;                  //Package weight
    struct packages *Cnext;      //Pointer to next package in the linked list
} package_t;



//Post office structure
typedef struct postOffice{
    int p;                  //Number of packages in this office
    int min_weight;         //Minium weight limit for package
    int max_weight;         //Maxium weight limit for package
    struct packages *pack;  //Pointer to first package in the linked list
    struct postOffice *Pnext;  //Pointer to next post office in the linked list
} postoffice_t;


//Division structure
typedef struct divisions{
    char name[10];                 //Division name
    int O;                         //Number of post office in the division
    struct postOffice *post;       //Pointer to first post office in the linked list
    struct divisions *Dnext;       //Pointer to next division in the linked list
} devisions_t;



int t;                   //Number of divisions
devisions_t *divi=NULL;  //Head pointer for divisions linked list


int main(){
    int q;                          //Number of queries
    devisions_t *last_divi=NULL;    //Temporary pointer to track last division
    //Read number of divisions
    scanf("%d",&t);
    
         
    //Process each division
    for(int i=0;i<t;i++){
        //Allocate memory for new division
        devisions_t *newNode1=(devisions_t*)malloc(sizeof(devisions_t));
        scanf("%s",&newNode1->name);   //Read the division name
        scanf("%d",&newNode1->O);      //Read number of post offices 
        newNode1->post=NULL;           //Initialize post office pointer
        newNode1->Dnext=NULL;          //Initialize next division pointer
        
        
        //Process each post office in the division
        postoffice_t *last_post=NULL;   //Temporary pointer to tack last post office
        for(int j=0;j<newNode1->O;j++){
            //Allocate memory for new post office
            postoffice_t *new_post=(postoffice_t*)malloc(sizeof(postoffice_t));
            
            //Read package count,min and max weight limits
            scanf("%d %d %d",&new_post->p,&new_post->min_weight,&new_post->max_weight);
            
            new_post->pack=NULL;        //Initialize package pointer
            new_post->Pnext=NULL;       //Initialize next post office pointer
            
            //Add to linked list of post offices
            if(last_post==NULL){
                newNode1->post=new_post;      //First post office in division
            }else{
                last_post->Pnext=new_post;    //Append to exsting list
            }
            last_post=new_post;               //Update last post office pointer
            
            
            
            //Process each package in this post office
            package_t *last_pack=NULL;  //Temporary pointer to track last package
            
            for(int k=0;k<new_post->p;k++){
               //Allocate memory for new package 
               package_t *new_pack=(package_t*)malloc(sizeof(package_t));
               scanf("%s %d",new_pack->id,&new_pack->weight); //Read package details
               
               new_pack->Cnext=NULL;         //Initialize next package pointer
               
               //Add to linked list of packages
               if(last_pack==NULL){
                   new_post->pack=new_pack;      //First package in post office
               }else{
                   last_pack->Cnext=new_pack;    //Append to existing list
               }
               last_pack=new_pack;               //Update last package pointer
            }
        }
        
        
        //Add division to the goal linked list
        if(divi==NULL){
            divi=newNode1;     //First division
        }else{          
            last_divi->Dnext=newNode1;   //Append to existing list
        }
        last_divi=newNode1;              //Update last division pointer
    }
    
    
    //Read the number of operations
    scanf("%d",&q);
    for(int i=0;i<q;i++){
        int index;
        scanf("%d",&index);    //Read the operation type
        
        if(index==1){                     //Print the operation
            char division_name[20];
            scanf("%s",division_name);
            print(division_name);
            
        }else if(index==2){               //Package transfer operation
            char source_name[20],target_name[20];
            int source_office_index,target_office_index;
            scanf("%s %d %s %d",source_name,&source_office_index,target_name,&target_office_index);
            packageTranfer(source_name,target_name,source_office_index,target_office_index);
            
        }else if(index==3){              //Find division with most packages
             mostpackages();
        }
        
    }
    
    freeMemory();                 //Free all allocated memory before exiting
    return 0;
}




//Function to print all packages in a division
void print(char *division_name){
    devisions_t *divisionS;
    //Find the requested division
    for(divisionS=divi;divisionS!=NULL;divisionS=divisionS->Dnext){
        if(strcmp(division_name,divisionS->name)==0){
            break;
        }
    }
    
    if(!divisionS) return ;           //Division not found
    
    printf("%s:\n",division_name);
    
    int index=0;
    postoffice_t *Ofice=divisionS->post;
    
    //Iterate through all post office in the division
    while(Ofice!=NULL){
        printf("       %d:\n",index);               //Print Office index
        package_t *pack=Ofice->pack;
        //Iterate through all packages in the office
        while(pack){
            printf("            %s\n",pack->id);    //Print package ID  
            pack=pack->Cnext;
        }
        index++;
        Ofice=Ofice->Pnext;
    }
    
}



// Function to find divison with most package
void mostpackages(){
    char name[20];
    int value=0;
    devisions_t *division=divi;
    
    //Iterate through all divisions
    while(division){
        int count=0;
        postoffice_t *office=division->post;
        
        //Count packages in all offices of this division
        while(office){
            count+=(office->p);
            office=office->Pnext;
        }
        //Track division with highest package count
        if(count>value){
            value=count;
            strcpy(name,division->name);
        }
        division=division->Dnext;
    }
    
    printf("Division with the most number of packages is %s\n",name);
    
}




//Function to transfer package between post offices
void packageTranfer(char *sourec_name,char *target_name,int source_index,int target_index){
    
    //Find target division and office 
    devisions_t *divisionT=NULL;
    postoffice_t *officeT=NULL;
    for(divisionT=divi;divisionT!=NULL;divisionT=divisionT->Dnext){
        if(strcmp(divisionT->name,target_name)==0){
            officeT=divisionT->post;
            
            //Navigate to the target office index
            for(int index =0;index<target_index && officeT;index++){
                officeT=officeT->Pnext;
            }
            break;
        }
    }
    
    
    //Find source division and office
    devisions_t *divisionS=NULL;
    postoffice_t *officeS=NULL;
    for(divisionS=divi;divisionS!=NULL;divisionS=divisionS->Dnext){
        if(strcmp(sourec_name,divisionS->name)==0){
            officeS=divisionS->post;
            
            //Navigate to the source office index
            for(int index=0;index<source_index && officeS;index++){
                officeS=officeS->Pnext;
            }
            break;
        }
    }
    
    //Check if both offices were found
    if(!divisionT || !divisionS || !officeT || !officeS){
        return;
    }
    
 
    package_t *curr=officeS->pack;     //Current package beigh examined
    package_t *pre=NULL;               //Previous package iin th list
    
    //Iterate through all packages in sourec office
    while(curr){
        //Check if package meets target office weight requirements
        if((officeT->min_weight<=curr->weight)&&(curr->weight<=officeT->max_weight)){
            
            //Update package counts
            (officeS->p)-=1;
            (officeT->p)+=1;
            
            //Remove package from source office
            if(pre == NULL){
                officeS->pack=curr->Cnext;    //Removing first package
            }else{
                pre->Cnext=curr->Cnext;       //Removing middle package
                
            }
    
            curr->Cnext=NULL;
            
            //Add package to target office at the end of list
            if(officeT->pack==NULL){
                officeT->pack=curr;         
            }else{
                package_t *lastpacket=officeT->pack;
                while(lastpacket->Cnext != NULL){
                    lastpacket=lastpacket->Cnext;
                }
                
                lastpacket->Cnext=curr; //Append to the end of list
            }
            
            //Move to next package in source office
            if(pre){
                curr=pre->Cnext;
                
            }else{
                curr=officeS->pack;
            }
        }else{
            //Package doesn't meet requirements,move to next
            pre=curr;
            curr=curr->Cnext;
        }
    }
}


//Function for free memory
void freeMemory(){
    devisions_t *currentDiv=divi;
    while(currentDiv !=NULL){
        
        postoffice_t *currentOffice=currentDiv->post;
        while(currentOffice!=NULL){
            package_t *currentPack=currentOffice->pack;
            while(currentPack!=NULL){
                package_t *tempPack=currentPack;
                currentPack=currentPack->Cnext;
                free(tempPack);   //Free each package
            }
            postoffice_t *tempOffice =currentOffice;
            currentOffice=currentOffice->Pnext;
            free(tempOffice);     //Free each post office
        }
        devisions_t *tempDiv=currentDiv;
        currentDiv=currentDiv->Dnext;
        free(tempDiv);            //Free each divison
     }
}

