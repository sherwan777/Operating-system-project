#include <semaphore.h>
#include <stdio.h>
#include <sys/types.h>
#include <wait.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#define TOBACCO 0
#define MATCHES 1
#define PAPER 2


sem_t Available; // 0
sem_t putNextItem; //0

bool itemsAvailable[3] = {false,false,false};



void* Agent(void* arg){

    while(true){

        printf("\n");


    int item1 = rand() % 3;

    int item2 = rand() % 3;


    while(item2==item1){

        item2 = rand() % 3;

     }

    itemsAvailable[item1] = true;
    itemsAvailable[item2] = true;

    if(item1==TOBACCO || item2==TOBACCO){
        printf("Agent Puts Tobacco\n");
    }
    if(item1==PAPER || item2==PAPER){
        printf("Agent Puts Paper\n");
    }
    if(item1==MATCHES || item2==MATCHES){
        printf("Agent Puts Matches\n");
    }

    


    sem_post(&Available);

    sem_wait(&putNextItem);


    }

}



void* Smoker1(void* arg){ //tobacco

    while(true){

    sem_wait(&Available);

    if(itemsAvailable[PAPER] && itemsAvailable[MATCHES]){

        printf("Smoker with Tobacco is smoking!\n");
        sleep(3);

        itemsAvailable[PAPER] = false;
        itemsAvailable[MATCHES] = false;

        sem_post(&putNextItem);
    }

    sem_post(&Available);

    }
            

} 


void* Smoker2(void* arg){ //matches

while(true){
  
    sem_wait(&Available);

    if(itemsAvailable[PAPER] && itemsAvailable[TOBACCO]){

        printf("Smoker with Matches is smoking!\n");
        sleep(3);

        itemsAvailable[PAPER] = false;
        itemsAvailable[TOBACCO] = false;

        sem_post(&putNextItem);
    }

    sem_post(&Available);
    
}

} 


void* Smoker3(void* arg){ //paper



while(true){

     sem_wait(&Available);

    if(itemsAvailable[MATCHES] && itemsAvailable[TOBACCO]){

        printf("Smoker with Paper is smoking!\n");
        sleep(3);

        itemsAvailable[MATCHES] = false;
        itemsAvailable[TOBACCO] = false;

        sem_post(&putNextItem);
    }

    sem_post(&Available);

}


} 

 

 int main(){

     srand(time(NULL));

     pthread_t th[4];
     sem_init(&Available,0,0);
     sem_init(&putNextItem,0,0);

    pthread_create(&th[0],NULL,&Agent,NULL);
    pthread_create(&th[1],NULL,&Smoker1,NULL);
    pthread_create(&th[2],NULL,&Smoker2,NULL);
    pthread_create(&th[3],NULL,&Smoker3,NULL);




    pthread_join(th[0],NULL);
    pthread_join(th[1],NULL);
    pthread_join(th[2],NULL);
    pthread_join(th[3],NULL);


    sem_destroy(&Available);
    sem_destroy(&putNextItem);
     




 }


