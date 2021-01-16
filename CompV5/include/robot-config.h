using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor motorLF;
extern motor motorLB;
extern motor motorRF;
extern motor motorRB;
extern inertial ISensor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );