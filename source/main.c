// Include the most common headers from the C standard library
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

// Include the main libnx system header, for Switch development
#include <switch.h>
//#include <twili.h>

// Sysmodules should not use applet*.
u32 __nx_applet_type = AppletType_None;

// Adjust size as needed.
#define INNER_HEAP_SIZE 0x80000
size_t nx_inner_heap_size = INNER_HEAP_SIZE;
char   nx_inner_heap[INNER_HEAP_SIZE];

void __libnx_initheap(void)
{
	void*  addr = nx_inner_heap;
	size_t size = nx_inner_heap_size;

	// Newlib
	extern char* fake_heap_start;
	extern char* fake_heap_end;

	fake_heap_start = (char*)addr;
	fake_heap_end   = (char*)addr + size;
}

// Init/exit services, update as needed.
void __attribute__((weak)) __appInit(void)
{
    Result rc;

    // Initialize default services.

    rc = smInitialize();
    if (R_FAILED(rc))
        fatalSimple(MAKERESULT(Module_Libnx, LibnxError_InitFail_SM));

    // Enable this if you want to use HID.
    rc = hidInitialize();
    if (R_FAILED(rc))
        fatalSimple(MAKERESULT(Module_Libnx, LibnxError_InitFail_HID));

    //Enable this if you want to use time.
    rc = timeInitialize();
    if (R_FAILED(rc))
        fatalSimple(MAKERESULT(Module_Libnx, LibnxError_InitFail_Time));

    __libnx_init_time();

    rc = fsInitialize();
    if (R_FAILED(rc))
        fatalSimple(MAKERESULT(Module_Libnx, LibnxError_InitFail_FS));

    fsdevMountSdmc();
}

void __attribute__((weak)) userAppExit(void);

void __attribute__((weak)) __appExit(void)
{
    // Cleanup default services.
    fsdevUnmountAll();
    fsExit();
    timeExit();//Enable this if you want to use time.
    hidExit();// Enable this if you want to use HID.
    smExit();
    //twiliExit();
}

// Main program entrypoint
int main(int argc, char* argv[])
{
    // Initialization code can go here.
    
    //twiliInitialize();

    mkdir("/orbit", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    time_t t = time(NULL);

    struct tm *tm = localtime(&t);

    char date[87];
    sprintf(date, "%d-%d-%d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);

    char filedate[104];

    sprintf(filedate, "/orbit/%s.orbit", date);

    FILE *f = fopen(filedate, "w");
    fclose(f);

    char *control[] = {"00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15", "16"};

    char keysNames[32][32] = {
        "00", "01", "02", "03",
        "04", "05", "06", "07",
        "08", "09", "10", "11",
        "12", "13", "14", "15",
        "16", "17", "18", "19",
        "20", "21", "22", "23",
        "24", "25", "26", "27",
        "28", "", "", ""
    };

    // Your code / main loop goes here.
    while(true){

        time_t t = time(NULL);

        struct tm *tm = localtime(&t);

        char datenow[87];

        memset(datenow, 0, sizeof(datenow));
        
        sprintf(datenow, "%d-%d-%d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);

        if(strcmp(datenow, date)){
            fclose(f);
            memset(date, 0, sizeof(date));
            sprintf(date, datenow);
            memset(filedate, 0, sizeof(filedate));
            sprintf(filedate, "/orbit/%s.orbit", date);
            f = fopen(filedate, "w");;
        }

        hidScanInput();

        u64 kDown1 = hidKeysDown(CONTROLLER_P1_AUTO);

        int i;
            for (i = 0; i < 32; i++)
            {
                if (kDown1 & BIT(i)) {
                    memset(date, 0, sizeof(date));
                    sprintf(date, datenow);
                    memset(filedate, 0, sizeof(filedate));
                    sprintf(filedate, "/orbit/%s.orbit", date);
                    f = fopen(filedate, "a");
                    fprintf(f, "%s %s 00\n", keysNames[i], control[hidGetControllerType(CONTROLLER_P1_AUTO)]);
                    fclose(f);
                }
            }    

        u64 kDown2 = hidKeysDown(CONTROLLER_PLAYER_2);

         
            for (i = 0; i < 32; i++)
            {
                if (kDown2 & BIT(i)) {
                    memset(date, 0, sizeof(date));
                    sprintf(date, datenow);
                    memset(filedate, 0, sizeof(filedate));
                    sprintf(filedate, "/orbit/%s.orbit", date);
                    f = fopen(filedate, "a");
                    fprintf(f, "%s %s 01\n", keysNames[i], control[hidGetControllerType(CONTROLLER_PLAYER_2)]);
                    fclose(f);
                }
            }    
            
        u64 kDown3 = hidKeysDown(CONTROLLER_PLAYER_3);

         
            for (i = 0; i < 32; i++)
            {
                if (kDown3 & BIT(i)) {
                    memset(date, 0, sizeof(date));
                    sprintf(date, datenow);
                    memset(filedate, 0, sizeof(filedate));
                    sprintf(filedate, "/orbit/%s.orbit", date);
                    f = fopen(filedate, "a");
                    fprintf(f, "%s %s 02\n", keysNames[i], control[hidGetControllerType(CONTROLLER_PLAYER_3)]);
                    fclose(f);
                }
            }    

        u64 kDown4 = hidKeysDown(CONTROLLER_PLAYER_4);

         
            for (i = 0; i < 32; i++)
            {
                if (kDown4 & BIT(i)) {
                    memset(date, 0, sizeof(date));
                    sprintf(date, datenow);
                    memset(filedate, 0, sizeof(filedate));
                    sprintf(filedate, "/orbit/%s.orbit", date);
                    f = fopen(filedate, "a");
                    fprintf(f, "%s %s 03\n", keysNames[i], control[hidGetControllerType(CONTROLLER_PLAYER_4)]);
                    fclose(f);
                }
            }   

        u64 kDown5 = hidKeysDown(CONTROLLER_PLAYER_5);

         
            for (i = 0; i < 32; i++)
            {
                if (kDown5 & BIT(i)) {
                    memset(date, 0, sizeof(date));
                    sprintf(date, datenow);
                    memset(filedate, 0, sizeof(filedate));
                    sprintf(filedate, "/orbit/%s.orbit", date);
                    f = fopen(filedate, "a");
                    fprintf(f, "%s %s 04\n", keysNames[i], control[hidGetControllerType(CONTROLLER_PLAYER_5)]);
                    fclose(f);
                }
            }    

        u64 kDown6 = hidKeysDown(CONTROLLER_PLAYER_6);

         
            for (i = 0; i < 32; i++)
            {
                if (kDown6 & BIT(i)) {
                    memset(date, 0, sizeof(date));
                    sprintf(date, datenow);
                    memset(filedate, 0, sizeof(filedate));
                    sprintf(filedate, "/orbit/%s.orbit", date);
                    f = fopen(filedate, "a");
                    fprintf(f, "%s %s 05\n", keysNames[i], control[hidGetControllerType(CONTROLLER_PLAYER_6)]);
                    fclose(f);
                }
            } 

        u64 kDown7 = hidKeysDown(CONTROLLER_PLAYER_7);

         
            for (i = 0; i < 32; i++)
            {
                if (kDown7 & BIT(i)) {
                    memset(date, 0, sizeof(date));
                    sprintf(date, datenow);
                    memset(filedate, 0, sizeof(filedate));
                    sprintf(filedate, "/orbit/%s.orbit", date);
                    f = fopen(filedate, "a");
                    fprintf(f, "%s %s 06\n", keysNames[i], control[hidGetControllerType(CONTROLLER_PLAYER_7)]);
                    fclose(f);
                }
            }    

        u64 kDown8 = hidKeysDown(CONTROLLER_PLAYER_8);

         
            for (i = 0; i < 32; i++)
            {
                if (kDown8 & BIT(i)) {
                    memset(date, 0, sizeof(date));
                    sprintf(date, datenow);
                    memset(filedate, 0, sizeof(filedate));
                    sprintf(filedate, "/orbit/%s.orbit", date);
                    f = fopen(filedate, "a");
                    fprintf(f, "%s %s 07\n", keysNames[i], control[hidGetControllerType(CONTROLLER_PLAYER_8)]);
                    fclose(f);
                }
            }
        /*touchPosition touch;
        u32 touch_count = hidTouchCount();
        int oldtouchy = 0;
        int oldtouchx = 0;
        for(i=0; i<touch_count; i++)
        {
            //Read the touch screen coordinates
            hidTouchRead(&touch, i);
            if(oldtouchy != touch.py){
                if(oldtouchx != touch.py){
                    oldtouchy = touch.py;
                    oldtouchx = touch.px;
                    printf("x=%03d y=%03d\n", touch.px, touch.py);
                }
            }
        }  */

        svcSleepThread(1E6);
    }
    // If you need threads, you can use threadCreate etc.

    // Deinitialization and resources clean up code can go here.
    return 0;
}
