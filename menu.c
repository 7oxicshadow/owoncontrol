#include <stdio.h>
#include "main.h"
#include "owon_commands.h"

void display_current_settings(void)
{
    printf("CH1 Coupling = %d, CH1 Probe Scale =  %d, CH1 Volt Scale = %d, CH1 Trace Position = %d\n",
            current_ch1_vars.ch_coupling,
            current_ch1_vars.ch_prb_scale,
            current_ch1_vars.ch_volt_range,
            current_ch1_vars.tracepos );
    printf("CH2 Coupling = %d, CH2 Probe Scale =  %d, CH2 Volt Scale = %d, CH2 Trace Position = %d\n",
            current_ch2_vars.ch_coupling,
            current_ch2_vars.ch_prb_scale,
            current_ch2_vars.ch_volt_range,
            current_ch2_vars.tracepos );
    printf("Memory Range = %d, Timebase = %d\n",current_memory_var,
            current_timebase_var);
}

void display_menu(void)
{
    int selection = 0;

    do
    {

        display_current_settings();
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
        printf("11. Force Trigger (Instant)\n");
        printf("12. 50pct trigger (Instant)\n");
        printf("13. 0v trigger (Instant)\n");
        printf("14. Set Horiz Position (Instant)\n");
        printf("15. Set Acqu Sample Mode (Instant)\n");
        printf("16. Set Acqu Peak Mode (Instant)\n");
        printf("17. Set Acqu Avg Mode (Instant)\n");
        printf("18. Set Trigger Options (Instant)\n");
        printf("19. Display Current Settings\n");
        printf("20. Send Changes.\n");
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
                set_trigger_opts();
                break;
            case 19:
                display_current_settings();
                break;
            case 20:
                printf("Writing Data...\n");
                check_changes();
                break;
            default:
                break;
        }
    } while(selection != 0);
}
