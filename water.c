#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t hMutex					= PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t h2Mutex					= PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t oMutex					= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  conditionHydrogen		= PTHREAD_COND_INITIALIZER;
pthread_cond_t  conditionH2ydrogen		= PTHREAD_COND_INITIALIZER;
pthread_cond_t  conditionOxygen			= PTHREAD_COND_INITIALIZER;

int currentHydrogenAtoms = 0;
int currentOxygenAtoms = 0;
int moleculesCreated = 0;

char hydrogenUsed = 0;
char oxygenUsed = 0;

void *addHydrogen(void *args) {
	pthread_mutex_lock(&hMutex);
	printf("ADDING one atom of HYDROGEN - (ID: %lu)\n", pthread_self());
	currentHydrogenAtoms++;
	pthread_cond_signal(&conditionH2ydrogen);
	pthread_cond_signal(&conditionHydrogen);

	while(currentOxygenAtoms < 1) {		
		pthread_cond_wait(&conditionOxygen, &hMutex);		
	}
	pthread_mutex_unlock(&hMutex);	

	pthread_mutex_lock(&h2Mutex);
	while(currentHydrogenAtoms < 2) {
		pthread_cond_wait(&conditionH2ydrogen, &h2Mutex);
	}

	//Create new molecule
	hydrogenUsed++;
	printf("USING one atom of HYDROGEN - (ID: %lu)\n", pthread_self());
	if (hydrogenUsed == 2 && oxygenUsed == 1) {
		hydrogenUsed = oxygenUsed = 0;
		currentHydrogenAtoms -= 2;
		currentOxygenAtoms--;
		moleculesCreated++;
		printf("MOLECULE OF WATER CREATED #%d\n", moleculesCreated);
	} 	

	pthread_mutex_unlock(&h2Mutex);	
	
}

void *addOxygen(void *args) {
	pthread_mutex_lock(&oMutex);
	printf("ADDING one atom of OXYGEN - (ID: %lu)\n", pthread_self());
	currentOxygenAtoms++;	
	pthread_cond_signal(&conditionOxygen);

	while(currentHydrogenAtoms < 2) {		
		pthread_cond_wait(&conditionHydrogen, &oMutex);		
	}
		
	//Creating new molecule	
	printf("USING one atom of OXYGEN - (ID: %lu)\n", pthread_self());
	oxygenUsed++;
	if (hydrogenUsed == 2 && oxygenUsed == 1) {
		hydrogenUsed = oxygenUsed = 0;
		currentHydrogenAtoms -= 2;
		currentOxygenAtoms--;
		moleculesCreated++;
		printf("MOLECULE OF WATER CREATED #%d\n", moleculesCreated);
	}		
	pthread_mutex_unlock(&oMutex);
}

int main() {
	int numberOfMolecules = 0;
	printf("Indique el numero de moleculas H20 a crear: ");
	scanf("%d", &numberOfMolecules);
	int nOfThreads = (numberOfMolecules * 2) + numberOfMolecules;
	int hCreated = 0;
	int oCreated = 0;
	pthread_t allThreads[nOfThreads];
	pthread_mutex_init( &hMutex, NULL );
	pthread_mutex_init( &oMutex, NULL );

	for (int i = 0; i < nOfThreads; ++i) {	
		if (hCreated < (numberOfMolecules * 2) && oCreated < numberOfMolecules) {
			if ((rand() % 100) >= 50) {
				//Create Oxygen
				pthread_create(&allThreads[i], NULL, addOxygen, NULL);			
				oCreated++;
			} else {
				//Create Hydrogen
				pthread_create(&allThreads[i], NULL, addHydrogen, NULL);
				hCreated++;
			}	
		} else if (hCreated < (numberOfMolecules * 2)) {
			pthread_create(&allThreads[i], NULL, addHydrogen, NULL);
			hCreated++;
		} else if (oCreated < numberOfMolecules) {			
			pthread_create(&allThreads[i], NULL, addOxygen, NULL);
			oCreated++;
		}		
		sleep(1);
	}

	for (int i = 0; i < nOfThreads; i++) {  
		pthread_join(allThreads[i],NULL);    
  	}	
	return 0;
}

