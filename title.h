#define display(text) cout<<"\t\t################################################################################\n\
\t\t##****************************************************************************##\n\
\t\t##*******************************|~~~~~~~~~~|*********************************##\n\
\t\t##*******************************| OUR BANK |*********************************##\n\
\t\t##*******************************|__________|*********************************##\n\
\t\t##****************************************************************************##\n\
\t\t################################################################################\n\
\t                                    **--"#text"--** \n";\
{\
        time_t times;\
        struct tm *timesinfo;\
        time(&times);\
        timesinfo=localtime(&times);\
        cout<<"\t\t\t\t\t\t\t\t TIME : "<<asctime(timesinfo);\
        currentTime=asctime(timesinfo);\
        currentTime+='\0';\
}