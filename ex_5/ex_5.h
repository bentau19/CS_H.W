#define MAX_WORKERS 50
#define MAX_PROJECTS 100
#define PREVIOUS_STEP 1
#define INITIAL_VAL 0
#define JOIN_WORKER_COND 1
#define MAKE_PROJECT_COND 2
#define WORKER_JOIN_PROJECT_COND 3
#define DISPLAY_PROJECT_COND 4
#define DISPLAY_WORKER_COND 5
#define WORK_ON_PROJECT_COND 6
#define LEAVE_COND 7
#define EXIT_COND 8
// Forward declarations
typedef struct Worker Worker;
typedef struct FeatureNode FeatureNode;
typedef struct Project Project;

enum Bool{FALSE,TRUE};

struct Worker
{
    char *name;
    Project **projects;
    int projectCount ;
};

struct FeatureNode
{
    char *feature;
    struct FeatureNode *next;
};

struct Project
{
    char *name;
    Worker **workers;
    int workerCount;
    FeatureNode *features;
};

void menu(void);
void clearInputBuffer(void);
char *getChars(void);
int isStringEmpty(const char *name);
int isWorkerNameExists(Worker *workers[], int workerCount, const char *name);
int isProjectNameExists(Project *projects[], int projectCount, const char *name);
void joinCompany(Worker *workers[], int *workerCount);
void openNewProject(Worker *workers[], int workerCount, Project *projects[], int *projectCount);
void workerJoinsProject(Worker *workers[], int workerCount, Project *projects[], int projectCount);
void addWorkerToProject(Worker *worker, Project *project);
void displayWorkers(Worker *workers[], int workerCount);
void displayProjects(Project *projects[], int projectCount);
void displayAllProjects(Project *projects[], int projectCount);
void displayAllWorkers(Worker *workers[], int workerCount);
void workOnProject(Worker *workers[], int workerCount, int *projectCount);
void addFeatureToProject(Project *project);
void removeFeatureFromProject(Project *project);
void leaveCompany(Worker *workers[], int *workerCount, Project *projects[], int *projectCount);
void freeProject(Project *project);
void freeFeatures(FeatureNode *head);
void freeAllAllocations(Worker *workers[], int workerCount, Project *projects[], int projectCount);
