#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ex_5.h"

/***********
*Name: Ben Tau
*Id: 325394997
*Assignment: ex_5
***********/


int main(){
    menu();
    return 0;
}
///make the string from the client input
char* getChars() {
    char* str = NULL;
    int sizeOfArr = INITIAL_VAL;
    do {
        str = realloc(str, (sizeOfArr+1) * sizeof(char));
        if (str == NULL) {
            free(str);
            return NULL;
        }
        scanf("%c", &str[sizeOfArr]);
        if(str[0] == '\n' && sizeOfArr == INITIAL_VAL) {
            free(str);
            return NULL;
        }

        sizeOfArr++;
    } while (str[sizeOfArr - PREVIOUS_STEP] != '\n');
    str[sizeOfArr - PREVIOUS_STEP] = '\0';
    return str;
}
///clear the input buffer
void clearInputBuffer(){
    scanf("%*[^\n]");
    scanf("%*c");
}
///check if the string is empty
int isStringEmpty(const char *name){
    return name==NULL;
}
///the menu of the program
void menu(){
    Worker* workers[MAX_WORKERS];
    int workerCount=INITIAL_VAL;
    Project* projects[MAX_PROJECTS];
    int projectCount=INITIAL_VAL;
    enum Bool isInProgress = TRUE;
    while (isInProgress){
        printf("Welcome!\n"
               "Please select the desired option:\n"
               "1. Join the company\n"
               "2. Open a new project\n"
               "3. Join an existing project\n"
               "4. See what projects are in work\n"
               "5. See which people are in what projects\n"
               "6. Work on existing project\n"
               "7. Leave the company\n"
               "8. Exit\n"
               "Enter your choice: ");
        int choice;
        scanf("%d", &choice);
        clearInputBuffer();
        switch(choice){
            case JOIN_WORKER_COND:
                joinCompany(workers, &workerCount);
                break;
            case MAKE_PROJECT_COND:
                openNewProject(workers,workerCount,projects,&projectCount);
                break;
            case WORKER_JOIN_PROJECT_COND:
                workerJoinsProject(workers, workerCount, projects, projectCount);
                break;
            case DISPLAY_PROJECT_COND:
                displayAllProjects(projects,projectCount);
                break;
            case DISPLAY_WORKER_COND:
                displayAllWorkers(workers, workerCount);
                break;
            case WORK_ON_PROJECT_COND:
                workOnProject(workers, workerCount, &projectCount);
                break;
            case LEAVE_COND:
                leaveCompany(workers, &workerCount,projects, &projectCount);
                break;
            case EXIT_COND:
                freeAllAllocations(workers,workerCount,projects,projectCount);
                printf("Exiting...\n");
                isInProgress=FALSE;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

///*mission num 1*///
///join to the company program
void joinCompany(Worker *workers[MAX_WORKERS], int *workerCount){
    if(*workerCount==MAX_WORKERS-PREVIOUS_STEP){
        printf("The company is at full capacity.\n");
        return;
    }
    printf("Enter the name of the new worker: ");
    Worker *newWorker = malloc(sizeof(Worker));
    if (newWorker == NULL) {
        exit(EXIT_FAILURE);
    }
    newWorker->name= (char *) getChars();
    if(isStringEmpty(newWorker->name)){
        printf("Invalid name\n");
        free(newWorker->name);
        free(newWorker);
        return;
    }
    if (isWorkerNameExists(workers,*workerCount,newWorker->name)){
        printf("A worker with this name already exists.\n"
               "There is not enough space in this company for both of us\n");
        free(newWorker->name);
        free(newWorker);
        return;
    }
    workers[*workerCount] = newWorker;
    workers[*workerCount]->projects=(Project**)malloc(sizeof (Project*));
    if (workers[*workerCount]->projects == NULL) {
        exit(EXIT_FAILURE);
    }
    workers[*workerCount]->projectCount=INITIAL_VAL;
    (*workerCount)++;
}

///check if the worker exists
int isWorkerNameExists(Worker *workers[], int workerCount, const char *name){
    for (int i = 0; i < workerCount; ++i) {
        if (strcmp(workers[i]->name,name) == 0)return TRUE;
    }
    return FALSE;
}
///*end mission num 1*///

///*mission num 2*///
///display all the workers
void displayWorkers(Worker *workers[], int workerCount){
    for (int i = 0; i < workerCount; ++i) {
        printf("%d. %s\n",(i+1),workers[i]->name);
    }
}
///check if the project is exist
int isProjectNameExists(Project *projects[], int projectCount, const char *name){
    for (int i = 0; i < projectCount; ++i) {
        if (strcmp(projects[i]->name,name) == 0)return TRUE;
    }
    return FALSE;
}
///func to open new project
void openNewProject(Worker *workers[], int workerCount, Project *projects[], int *projectCount){
    //check if the projects is full
    if(*projectCount==MAX_PROJECTS-PREVIOUS_STEP){
        printf("Maximum number of projects reached.\n");
        return;
    }
    //check if there is workers
    if(workerCount==INITIAL_VAL){
        printf("There are no workers in the company yet, please join the company first.\n");
        return;
    }
    printf("Who are you? Choose a number:\n");
    displayWorkers(workers, workerCount);
    printf("Enter your choice: ");
    int choice = INITIAL_VAL;
    scanf("%d",&choice);
    clearInputBuffer();
    // check if the val in the range
    if (choice>workerCount||choice<1){
        printf("Invalid selection.\n");
        return;
    }
    printf("Enter the name of the new project: ");
    Project *newProject = (Project*)malloc(sizeof(Project));
    if (newProject == NULL) {
        exit(EXIT_FAILURE);
    }
    newProject->name = getChars();
    if(isStringEmpty(newProject->name)){
        printf("Invalid name\n");
        free(newProject->name);
        free(newProject);
        return;
    }
    if(isProjectNameExists(projects, *projectCount, newProject->name)) {
        printf("A project with this name already exists.\n"
               "Better be more creative\n");
        free(newProject->name);
        free(newProject);
        return;
    }
    //initial the project
    newProject->workers= (Worker **) malloc(sizeof(Worker*));
    if (newProject->workers == NULL) {
        exit(EXIT_FAILURE);
    }
    newProject->workers[0] = workers[choice-PREVIOUS_STEP];
    newProject->workerCount=1;
    newProject->features=(FeatureNode *) malloc(sizeof(FeatureNode));
    if (newProject->features == NULL) {
        exit(EXIT_FAILURE);
    }
    newProject->features->feature=NULL;
    projects[*projectCount] = newProject;
    workers[choice-PREVIOUS_STEP]->projects = (Project **) realloc(workers[choice-PREVIOUS_STEP]->projects,sizeof(Project*)*( workers[choice-PREVIOUS_STEP]->projectCount+1));
    if (workers[choice-PREVIOUS_STEP]->projects == NULL) {
        exit(1);
    }
    workers[choice-PREVIOUS_STEP]->projects[workers[choice-PREVIOUS_STEP]->projectCount]=projects[*projectCount];
    workers[choice-PREVIOUS_STEP]->projectCount++;
    (*projectCount)++;
}

///*end mission num 2*///

///*mission num 3*///
///display all the projects
void displayProjects(Project *projects[], int projectCount){
    for (int i = 0; i < projectCount; ++i) {
        printf("%d. %s (Workers: %d)\n",(i+1),projects[i]->name,projects[i]->workerCount);
    }
}
///worker join to project func
void workerJoinsProject(Worker *workers[], int workerCount, Project *projects[], int projectCount){
    //check if all params are good
    if (workerCount==INITIAL_VAL){
        printf("There are no workers in the company yet, please join the company first.\n");
        return;
    }
    if (projectCount==INITIAL_VAL){
        printf("There are no projects in the company yet, please create one first.\n");
        return;
    }
    //ask the client for params
    printf("Select a worker to join a project:\n");
    displayWorkers(workers,workerCount);
    printf("Enter the worker's number: ");
    int workerNum;
    scanf("%d",&workerNum);
    clearInputBuffer();
    if(workerNum>workerCount||workerNum<1){
        printf("Invalid worker selection.\n");
        return;
    }
    printf("Select a project to join:\n");
    displayProjects(projects, projectCount);
    printf("Enter the project's number: ");
    int projectNum;
    scanf("%d",&projectNum);
    clearInputBuffer();
    //check if the val are good
    if(projectNum>projectCount||projectNum<1){
        printf("Invalid project selection.\n");
        return;
    }
    //check if the worker already in the project
    for (int i = 0; i < projects[projectNum-PREVIOUS_STEP]->workerCount; ++i) {
        if(strcmp(projects[projectNum-PREVIOUS_STEP]->workers[i]->name,workers[workerNum-PREVIOUS_STEP]->name)==0){
            printf("This worker is already part of the project '%s'.\n",projects[projectNum-PREVIOUS_STEP]->name);
            return;
        }
    }
    //check if the project is full
    if(projects[projectNum-PREVIOUS_STEP]->workerCount==4){
        printf("Project is full.\n");
        return;
    }
    addWorkerToProject(workers[workerNum-PREVIOUS_STEP],projects[projectNum-PREVIOUS_STEP]);
}

///the actual add worker to project function
void addWorkerToProject(Worker *worker, Project *project) {
    project->workers = realloc(project->workers, (project->workerCount + 1) * sizeof(Worker*));
    if (project->workers == NULL) {
        exit(1);
    }
    project->workers[project->workerCount] = worker;
    project->workerCount++;
    worker->projects = realloc(worker->projects, (worker->projectCount + 1) * sizeof(Project*));
    if (worker->projects == NULL) {
        exit(1);
    }
    worker->projects[worker->projectCount] = project;
    worker->projectCount++;
}


///*end mission num 3*///

///*mission num 4*///
//display all the projects
void displayAllProjects(Project *projects[], int projectCount){
    if (projectCount==INITIAL_VAL){
        printf("There are no projects to display.\n");
        return;
    }
    for (int i = 0; i < projectCount; ++i) {
        printf("Project: %s\n"
               "  Workers in this project:\n", projects[i]->name);
        for (int j = 0; j < projects[i]->workerCount; ++j) {
            printf("    - %s\n",projects[i]->workers[j]->name);
        }
        printf( "  Features of the project:\n");
        if (projects[i]->features->feature==NULL)printf("    No features\n");
        else {
            FeatureNode* tempFeature=projects[i]->features;
            while (tempFeature->feature!=NULL){
                printf("    - %s\n",tempFeature->feature);
                tempFeature=tempFeature->next;
            }
        }
        printf("\n");
    }
}
///*end mission num 4*///

///*mission num 5*///
//display all the workers
void displayAllWorkers(Worker *workers[], int workerCount){
    if (workerCount==INITIAL_VAL){
        printf("There are no workers to display.\n");
        return;
    }
    for (int i = 0; i < workerCount; ++i) {
        printf("Worker: %s\n", workers[i]->name);
        if (workers[i]->projectCount==INITIAL_VAL){
            printf("  Not involved in any projects.\n\n");
        }else{
            printf("  Projects this worker is involved in:\n");
            for (int j = 0; j < workers[i]->projectCount; ++j) {
                printf("    - %s\n",workers[i]->projects[j]->name);
            }}
        printf("\n");
    }
}
///*end mission num 5*///

///*mission num 6*///
//manu to the func of add or remove feature
void workOnProject(Worker *workers[], int workerCount, int *projectCount) {
    //check if all params are good
    if (workerCount == INITIAL_VAL) {
        printf("There are no workers in the company yet, please join the company first.\n");
        return;
    }
    if (*projectCount == INITIAL_VAL) {
        printf("There are no projects in the company yet, please create a project first.\n");
        return;
    }
    printf("Select a worker:\n");
    displayWorkers(workers, workerCount);
    printf("Enter the worker's number: ");
    int workerIdx;
    scanf("%d", &workerIdx);
    clearInputBuffer();
    if (workerIdx < 1 || workerIdx > workerCount) {
        printf("Invalid worker selection.\n");
        return;
    }
    if(workers[workerIdx - PREVIOUS_STEP]->projectCount==0){
        printf("This worker is not involved in any projects.\n");
        return;
    }
    printf("Select a project:\n");
    for (int i = 0; i < workers[workerIdx - PREVIOUS_STEP]->projectCount; ++i) {
        printf("%d. %s\n", i + 1, workers[workerIdx - PREVIOUS_STEP]->projects[i]->name);
    }
    printf("Enter the project number: ");
    int projectIdx;
    scanf(" %d", &projectIdx);
    clearInputBuffer();
    if (projectIdx < 1 || projectIdx > workers[workerIdx - PREVIOUS_STEP]->projectCount) {
        printf("Invalid project selection.\n");
        return;
    }
    printf("Do you want to add or remove a feature? (add/remove): ");
    char *choice;
    choice = getChars();
    if(isStringEmpty(choice)){
        printf("Invalid choice.\n");
        free(choice);
        return;
    }
    const char add[]="add";
    const char remove[]="remove";
    //check if all params are good
    if (strcmp(add, choice) == 0) {
        addFeatureToProject(workers[workerIdx-PREVIOUS_STEP]->projects[projectIdx - PREVIOUS_STEP]);
    } else if (strcmp(remove, choice) == 0) {
        if(workers[workerIdx-PREVIOUS_STEP]->projects[projectIdx-PREVIOUS_STEP]->features->feature!=NULL)
            removeFeatureFromProject(workers[workerIdx-PREVIOUS_STEP]->projects[projectIdx-PREVIOUS_STEP]);
        else printf("There are no features to remove.\n");
    } else {
        printf("Invalid choice.\n");
        free(choice);
        return;
    }
    free(choice);
}
//remove the feature
void removeFeatureFromProject(Project *project){
    printf("Select a feature to remove:\n");
    FeatureNode* currentFeature = project->features;
    int counter = 1;
    while (currentFeature->feature!=NULL){
        printf("%d. %s\n",counter,currentFeature->feature);
        counter++;
        currentFeature=currentFeature->next;
    }
    printf("Enter your choice: ");
    int choice;
    scanf("%d",&choice);
    clearInputBuffer();
    if(choice>counter-1||choice<1){
        printf("Invalid selection.\n");
        return;
    }

    currentFeature=project->features;
    for (int i = 0; i < choice-PREVIOUS_STEP*2; ++i) {
        currentFeature=currentFeature->next;
    }
    if(choice==1){
        project->features=project->features->next;
        free(currentFeature->feature);
        free(currentFeature);
        return;
    }
    FeatureNode* deletedFeature = currentFeature->next;
    currentFeature->next=currentFeature->next->next;
    free(deletedFeature->feature);
    free(deletedFeature);

}
//add the feature
void addFeatureToProject(Project *project){
    printf("Enter the new feature: ");
    char *featureName = NULL;
    featureName= getChars();
    if(isStringEmpty(featureName)){
        printf("Invalid name\n");
        free(featureName);
        return;
    }
    enum Bool flag =TRUE;
    FeatureNode* currentFeature = project->features;
    while (flag){
        if (currentFeature->feature==NULL){
            currentFeature->feature= featureName;
            currentFeature->next=(FeatureNode *) malloc(sizeof(FeatureNode));
            if (currentFeature->next == NULL) {
                exit(EXIT_FAILURE);
            }
            currentFeature->next->feature=NULL;
            return;
        }
        if (strcmp(currentFeature->feature, featureName) == 0){
            printf("This feature already exists in the project.\n");
            free(featureName);
            return;
        }

        currentFeature = currentFeature->next;

    }
}
///*end mission num 6*///

///*mission num 7*///
// find the index of a project
int findProjectIdx(Project *projects[],int projectsCount,char *name){
    for (int j = 0; j < projectsCount; ++j) {
        if(strcmp(projects[j]->name,name)==0)return j;
    }
    return 0;
}
//free the project
void freeProject(Project *project){
    free(project->workers);
    free(project->name);
    freeFeatures(project->features);
    free(project->features);
    free(project);
}
//delete the worker from the array
void deleteWorkerFromArray(Project *currentProject,int idx){
    for (int i = 0; i <currentProject->workerCount-idx-PREVIOUS_STEP; ++i)
        currentProject->workers[idx+i]=currentProject->workers[idx+i+1];
    currentProject->workerCount-=PREVIOUS_STEP;
    currentProject->workers=(Worker**) realloc(currentProject->workers,sizeof (Worker*)*currentProject->workerCount);
    if (currentProject->workers == NULL) {
        exit(1);
    }
}
// find the index of a worker
int findWorkerIdx(Project *currentProject,char *name){
    for (int j = 0; j < currentProject->workerCount; ++j) {
        if(strcmp(currentProject->workers[j]->name,name)==0)return j;
    }
    return 0;
}
//delete the worker from the projects
void deleteWorkerFromProjects(Worker* deletedWorker,Project *projects[], int *projectCount){
    for (int i = 0; i < deletedWorker->projectCount; ++i) {
        Project *currentProject= deletedWorker->projects[i];
        if(currentProject->workerCount == 1) {
            int projectIdx=findProjectIdx(projects, *projectCount,currentProject->name)+1;
            for (int j = 0; j < *projectCount-projectIdx; ++j) {
                projects[projectIdx-PREVIOUS_STEP+j]=projects[projectIdx+j];
            }
            *projectCount-=PREVIOUS_STEP;
            freeProject(currentProject);
        }
        else{
            deleteWorkerFromArray(currentProject,findWorkerIdx( currentProject, deletedWorker->name));
        }
    }
}
//free the worker
void freeWorker(Worker* deletedWorker){
    free(deletedWorker->name);
    free(deletedWorker->projects);
    free(deletedWorker);
}
// leave the company function
void leaveCompany(Worker *workers[], int *workerCount, Project *projects[], int *projectCount){
    if(*workerCount==0){
        printf("There are no workers in the company yet, please join the company first.\n");
        return;
    }
    printf("Select a worker to leave the company:\n");
    displayWorkers(workers, *workerCount);
    printf("Enter the worker's number: ");
    int workerIdx;
    scanf("%d",&workerIdx);
    clearInputBuffer();
    if (*workerCount<workerIdx||workerIdx<1){
        printf("Invalid worker selection.\n");
        return;
    }
    Worker* deletedWorker = workers[workerIdx-PREVIOUS_STEP];
    //this func remove the worker from the array of the workers
    for (int i = 0; i < *workerCount-workerIdx; ++i) {
        workers[workerIdx-PREVIOUS_STEP+i]=workers[workerIdx+i];
    }
    *workerCount-=PREVIOUS_STEP;
    deleteWorkerFromProjects(deletedWorker,projects, projectCount);
    freeWorker(deletedWorker);

}
///*end mission num 7*///


///*mission num 8*///
//free the features
void freeFeatures(FeatureNode *head){
    if (head->feature!=NULL){
        freeFeatures(head->next);
        free(head->next);
        free(head->feature);
    }
}
//free all the allocations
void freeAllAllocations(Worker *workers[], int workerCount, Project *projects[], int projectCount){
    for (int i = 0; i < workerCount; ++i) {
        freeWorker(workers[i]);
    }
    for (int i = 0; i < projectCount; ++i) {
        freeProject(projects[i]);
    }
}
///*end mission num 8*///