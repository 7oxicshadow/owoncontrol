#include <stdio.h>
#include "main.h"
#include "owon_commands.h"

void display_menu(void)
{
    int selection = 0;

    do
    {
        printf("\n");
        printf("1.  Change CH1 Coupling\n");
        printf("2.  Change CH1 Probe Scale\n");
        printf("3.  Change CH1 Volt Scale\n");
        printf("4.  Change CH1 Trace Position\n");
        printf("5.  Change CH2 Coupling\n");
        printf("6.  Change CH2 Probe Scale\n");
        printf("7.  Change CH2 Volt Scale\n");
        printf("8.  Change CH2 Trace Position\n");
        printf("9.  Change Memory Range\n");
        printf("10. Change Timebase\n");
        printf("11. Force Trigger\n");
        printf("12. 50pct trigger\n");
        printf("13. 0v trigger\n");
        printf("14. Set Horiz Position\n");
        printf("15. Set Acqu Sample Mode\n");
        printf("16. Set Acqu Peak Mode\n");
        printf("17. Set Acqu Avg Mode\n");
        printf("18. Set Trigger Options\n");
        printf("19. Autoset\n");
        printf("20. Self Cal\n");
        printf("21. Factory Reset\n");
        printf("\n");
        printf("0.  Quit\n");
        printf("\n");

        scanf("%d", &selection);

        switch(selection)
        {
            case 1:
                set_coupling(CHANNEL_1);
                break;
            case 2:
                set_probescale(CHANNEL_1);
                break;
            case 3:
                set_voltscale(CHANNEL_1);
                break;
            case 4:
                set_tracepos(CHANNEL_1);
                break;
            case 5:
                set_coupling(CHANNEL_2);
                break;
            case 6:
                set_probescale(CHANNEL_2);
                break;
            case 7:
                set_voltscale(CHANNEL_2);
                break;
            case 8:
                set_tracepos(CHANNEL_2);
                break;
            case 9:
                set_memrange();
                break;
            case 10:
                set_timebase();
                break;
            case 11:
                force_trigger();
                break;
            case 12:
                set_50pct_trigger();
                break;
            case 13:
                set_0_trigger();
                break;
            case 14:
                set_horiz_trigger_pos();
                break;
            case 15:
                set_acqu_mode(ACQU_SAMPLE);
                break;
            case 16:
                set_acqu_mode(ACQU_PEAK);
                break;
            case 17:
                set_avg_acqu_mode();
                break;
            case 18:
                select_trigger_type();
                break;
            case 19:
                send_autoset_command();
                break;
            case 20:
                send_self_cal_command();
                break;
            case 21:
                send_factory_reset_command();
                break;
            default:
                break;
        }
    } while(selection != 0);
}
