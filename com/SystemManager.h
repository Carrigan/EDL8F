#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

// System Use
void 	SystemManager_preSetup(void);
void 	SystemManager_postSetup(void);

// WKT
void setupWktTimer(unsigned int pPeriod);
void resetWktTimer(void);
void changeWktTimer(unsigned int pPeriod);
void stopWktTimer(void)


#endif
