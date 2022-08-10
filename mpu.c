//#include "mpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//define type iam_t
typedef struct iam_t {
    int clientID;
    char role;
    int methodID;
}iam_t;

//define cache, which contains the service as well as last permission decision
typedef struct cache{
    iam_t *service;
    int permission;
}cache;


#define NUM_SERVICE 3
//define parameters
int clientID = 100;
enum role {ROLE_UNAUTH, ROLE_DRIVER, ROLE_FRIEND, ROLE_FAMILY, ROLE_OWNER, ROLE_SALES, ROLE_SERVICE, ROLE_MAINTAIN, ROLE_ADMIN}; 
//role based system in groups
int method = 1;
bool check = false;
iam_t *unknownService = {NULL};
//acl is in the form of a matrix (2D array)
int acl[10][9]; 

/*
先按照flow图标画一个伪代码
cache先找一个临时数组存着（到时候问）
match acl要search加compare矩阵，先在本地做一个，能有output到下一步
*/

//initialize iam service
iam_t *soa_iam_init(iam_t *iam){
    //define ID, role, method
    iam_t *temp = iam;
    temp->clientID = clientID;
    enum role myrole;
    myrole = ROLE_DRIVER;
    temp->role = myrole;
    temp->methodID = method;
    return temp;
}

//check if service exist in cache
bool inCache(iam_t *iam){
    if(iam->clientID != 0){
        return true;
    }
    return false;
}

//check if session exist
bool sessionExist(int checkID){
    if(checkID > 0){
        return true;
    }
    return false;
}

void soa_iam_destroy(iam_t *iam);

int soa_iam_logon(iam_t *iam, const char *service_name, char *out, int olen);

int soa_iam_grant(iam_t *iam, const char *client_name, char *out, int olen);

int soa_iam_acl(iam_t *iam, const char *client_name, const char *method);

//get sesssions helper
bool get_session(int clientID){
    if(sessionExist(clientID) == true){
        return true;
    }
    return false;
}

// iam_t *soa_iam_init (){
//     char action = 'y';
//     iam_t *temp = soa_iam_init(action);
//     return temp;
// }


int main(int argc, char const *argv[])
{   
    //fill ACL with testing data
    int temp = 1;
    for(int a = 0; a < 10; a++){
        for(int b = 0; b < 9; b++){
            acl[a][b] = temp;
            if(temp == 1){
                temp = 0;
            }
            else{
                temp = 1;
            }
        }
    }
    //array of cache
    cache *mycache = malloc(50 * sizeof(cache));
    //create a testing entry
    mycache[0].service->clientID = 1;
    mycache[0].service->role = ROLE_DRIVER;
    mycache[0].service->methodID = 1;
    mycache[0].permission = 1;
    int index = 0;

    iam_t *myService = unknownService;
    //initialize service and get client, role, method
    myService = soa_iam_init(myService);
    int myID = myService->clientID;
    char myRole = myService->role;
    int myMethod = myService->methodID;
    // cache[0] = *myService;
    //If session exists
    if(get_session(myID) == true){
            //return cache result
        printf("Session exists\n");
        for(int i = 0; i < (sizeof(cache)/sizeof(iam_t)); i++){
            //iterate through the cache to find the target service
            if(mycache->service->role == myService->role && mycache[i].service->clientID == myService->clientID && mycache[i].service->methodID == myService->methodID){
                //if the service is found
                printf("Found in Cache\n");
                if(mycache[i].permission == 1){
                    //check the permission stored in cache
                    printf("Access Authorized\n");
                    return 0;
                }
                else{
                    printf("Access Denied\n");
                    // exit();
                    return 0;
                }
            }
        }
        //not found in cache
        printf("Not Found in Cache\n");
        //compare and match ACL since it's not found in cache
        if(acl[myService->methodID][myService->role] == 1){
            //approved according to acl
            printf("Access Authorized");
            //store in cache
            index ++;
            mycache[index].service->clientID = myService->clientID;
            mycache[index].service->methodID = myService->methodID;
            mycache[index].service->role = myService->role;
            mycache[index].permission = 1;
        }
        else{
            printf("Access Denied");
            //store in cache
            index ++;
            mycache[index].service->clientID = myService->clientID;
            mycache[index].service->methodID = myService->methodID;
            mycache[index].service->role = myService->role;
            mycache[index].permission = 0;
        }
        //store results in cache and return
        return 0;
        
    }else{
        //compare and match ACL
        printf("Session does not exist\n");
        //session not found, now we compare to the ACL for permission authorization
        if(acl[myService->methodID][myService->role] == 1){
            //approved according to acl
            printf("Access Authorized");
            //Store in cache
            index ++;
            mycache[index].service->clientID = myService->clientID;
            mycache[index].service->methodID = myService->methodID;
            mycache[index].service->role = myService->role;
            mycache[index].permission = 1;
        }
        else{
            printf("Access Denied");
            //store in cache
            index ++;
            mycache[index].service->clientID = myService->clientID;
            mycache[index].service->methodID = myService->methodID;
            mycache[index].service->role = myService->role;
            mycache[index].permission = 0;
        }
        return 0;
        //store session and result in cache
        //return

    }
    //clientID = getInfo();
    //return results here...
    return 0;
}
