#include <stdio.h>
#include <libusb.h>
#include "main.h"
#include "usb_interface.h"
#include "owon_commands.h"

void set_coupling(channel_e chan)
{
    int value = 0;

    if (chan < NUM_CHANNEL_ENTRIES)
    {
        printf("0=DC_CPL, 1=AC_CPL, 2=GND_CPL\n");
        scanf("%d", &value);

        if(value < NUM_CPL_ENTRIES)
        {
            coupling_data[9] = chan;
            coupling_data[11] = value;
            printf("Updating CH1 Coupling\n");
            send_usb_data(coupling_data, sizeof(coupling_data));
        }
        else
            printf("Value out of range!\n");
    }
    else
    {
        printf("Channel out of range!\n");
    }
}

void set_probescale(channel_e chan)
{
    int value = 0;

    if (chan < NUM_CHANNEL_ENTRIES)
    {
        printf("0=PRB_X1, 1=PRB_X10, 2=PRB_X100, 3=PRB_X1000\n");
        scanf("%d", &value);

        if(value < NUM_PRB_ENTRIES)
        {
            probe_scale_data[9] = chan;
            probe_scale_data[11] = value;
            printf("Updating CH1 Probe Scale\n");
            send_usb_data(probe_scale_data, sizeof(probe_scale_data));
        }
        else
        {
            printf("Value out of range!\n");
        }
    }
    else
    {
        printf("Channel out of range!\n");
    }
}

void set_voltscale(channel_e chan)
{
    int value = 0;

    if (chan < NUM_CHANNEL_ENTRIES)
    {

        printf("0=VOLT_2MV,  1=VOLT_5MV,   2=VOLT_10MV,  3=VOLT_20MV\n");
        printf("4=VOLT_50MV, 5=VOLT_100MV, 6=VOLT_200MV, 7=VOLT_500MV\n");
        printf("8=VOLT_1V,   9=VOLT_2V,    10=VOLT_5V,   11=VOLT_10V\n");
        scanf("%d", &value);

        if(value < NUM_VOLT_ENTRIES)
        {
            volt_range_data[9] = chan;
            volt_range_data[11] = value;
            printf("Updating CH2 Volt Range\n");
            send_usb_data(volt_range_data, sizeof(volt_range_data));
        }
        else
        {
            printf("Value out of range!\n");
        }
    }
    else
    {
        printf("Channel out of range!\n");
    }
}

void set_tracepos(channel_e chan)
{
    int value = 0;

    if (chan < NUM_CHANNEL_ENTRIES)
    {
        printf("Enter decimal value between -250 and +250\n");
        scanf("%d", &value);

        if( (value >= -250) && (value <= 250) )
        {
            tracepos_data[9] = chan;
            tracepos_data[11] = (char) ((value >> 24) & 0x000000FF);
            tracepos_data[12] = (char) ((value >> 16) & 0x000000FF);
            tracepos_data[13] = (char) ((value >> 8) & 0x000000FF);
            tracepos_data[14] = (char) ((value) & 0x000000FF);
            printf("Updating CH2 Trace Position\n");
            send_usb_data(tracepos_data, sizeof(tracepos_data));
        }
        else
        {
            printf("Value out of range!\n");
        }
    }
    else
    {
        printf("Channel out of range!\n");
    }
}

void set_memrange(void)
{
    int value = 0;

    printf("0=MEM_1K, 1=MEM_10K, 2=MEM_100K, 3=MEM_1M, 4=MEM_10M\n");
    scanf("%d", &value);

    if(value < NUM_MEM_ENTRIES)
    {
        memory_range_data[9] = value;
        printf("Updating Memory Depth\n");
        send_usb_data(memory_range_data, sizeof(memory_range_data));
    }
    else
    {
        printf("Value out of range!\n");
    }
}

void set_timebase(void)
{
    int value = 0;

    printf("0=TBASE_2NS,    1=TBASE_5NS,    2=TABSE_10NS,   3=TABSE_20NS\n");
    printf("4=TBASE_50NS,   5=TBASE_100NS,  6=TBASE_200NS,  7=TBASE_500NS\n");
    printf("8=TBASE_1US,    9=TBASE_2US,    10=TBASE_5US,   11=TBASE_10US\n");
    printf("12=TBASE_20US,  13=TBASE_50US,  14=TBASE_100US, 15=TBASE_200US\n");
    printf("16=TBASE_500US, 17=TBASE_1MS,   18=TBASE_2MS,   19=TBASE_5MS\n");
    printf("20=TBASE_10MS,  21=TBASE_20MS,  22=TBASE_50MS,  23=TBASE_100MS\n");
    printf("24=TBASE_200MS, 25=TBASE_500MS, 26=TBASE_1S,    27=TBASE_2S\n");
    printf("28=TBASE_5S,    29=TBASE_10S,   30=TBASE_20S,   31=TBASE_50S\n");
    printf("32=TBASE_100S\n");
    scanf("%d", &value);

    if(value < NUM_TBASE_ENTRIES)
    {
        timebase_data[10] = value;
        printf("Updating Timebase\n");
        send_usb_data(timebase_data, sizeof(timebase_data));
    }
    else
    {
        printf("Value out of range!\n");
    }
}

void force_trigger(void)
{
    printf("Send Force Trigger Command\n");
    send_usb_data(force_trig_data, sizeof(force_trig_data));
}

void set_50pct_trigger(void)
{
    printf("Send 50pct Trigger Command\n");
    send_usb_data(set_50pct_trig_data, sizeof(set_50pct_trig_data));
}

void set_0_trigger(void)
{
    printf("Send 0 Trigger Command\n");
    send_usb_data(set_0_trig_data, sizeof(set_0_trig_data));
}

void set_horiz_trigger_pos(void)
{
    int value = 0;

    printf("Enter decimal value between -10000 and +10000\n");

    scanf("%d", &value);

    if( (value >= -10000) && (value <= 10000) )
    {
        hor_trigger_data[10] = (char) ((value >> 24) & 0x000000FF);
        hor_trigger_data[11] = (char) ((value >> 16) & 0x000000FF);
        hor_trigger_data[12] = (char) ((value >> 8) & 0x000000FF);
        hor_trigger_data[13] = (char) (value & 0x000000FF);

        printf("Send Horiz Pos Command\n");
        send_usb_data(hor_trigger_data, sizeof(hor_trigger_data));
    }
    else
    {
        printf("Value out of range!\n");
    }
}

void set_acqu_mode(acqu_e mode)
{
    int value = 0;

    if(mode < NUM_ACQU_ENTRIES)
    {
        acqu_mode_data[9] = mode;

        printf("Send Acquisition Mode Command\n");
        send_usb_data(acqu_mode_data, sizeof(acqu_mode_data));
    }
}

void set_avg_acqu_mode(void)
{
    int value = 0;

    printf("0=4_SAMPLES, 1=16_SAMPLES, 2=64_SAMPLES, 3=128_SAMPLES\n");
    scanf("%d", &value);

    if(value < NUM_SAMPLE_ENTRIES)
    {
        acqu_avg_mode_data[10] = value;

        printf("Send Avg Acquisition Mode Command\n");
        send_usb_data(acqu_avg_mode_data, sizeof(acqu_avg_mode_data));
    }
    else
    {
        printf("Value out of range\n");
    }
}

void select_trigger_type(void)
{
    int value = 0;

    printf("0=TRIG_TYPE_SINGLE 1=TRIG_TYPE_ALT 2=TRIG_TYPE_VIDEO\n");
    scanf("%d", &value);

    if(value < NUM_TRIG_MODE_ENTRIES)
    {
        switch(value)
        {
            case TRIG_TYPE_SINGLE:
                set_edge_or_alt_trigger(TRIG_TYPE_SINGLE);
                break;
            case TRIG_TYPE_ALT:
                set_edge_or_alt_trigger(TRIG_TYPE_ALT);
                break;
            case TRIG_TYPE_VIDEO:
                set_video_trigger();
                break;
            default:
                break;
        }
    }
    else
    {
        printf("Value out of range\n");
    }

}

void set_edge_or_alt_trigger(int mode)
{
    int value = 0;

    printf("0=CHANNEL_1 1=CHANNEL_2\n");
    scanf("%d", &value);

    if(value < NUM_CHANNEL_ENTRIES)
    {
            edge_trigger_data[10] = value;
            edge_trigger_data[18] = value;
            edge_trigger_data[26] = value;
            edge_trigger_data[37] = value;
            edge_trigger_data[45] = value;
    }
    else
    {
            printf("Out of range\n");
            return;
    }

    switch(mode)
    {
        case TRIG_TYPE_SINGLE:
            edge_trigger_data[9] = 0x73;
            edge_trigger_data[17] = 0x73;
            edge_trigger_data[25] = 0x73;
            edge_trigger_data[36] = 0x73;
            edge_trigger_data[44] = 0x73;
            break;
        case TRIG_TYPE_ALT:
            edge_trigger_data[9] = 0x61;
            edge_trigger_data[17] = 0x61;
            edge_trigger_data[25] = 0x61;
            edge_trigger_data[36] = 0x61;
            edge_trigger_data[44] = 0x61;
            break;
        default:
            printf("Out of range\n");
            return;
            break;
    }

    printf("0=RISING 1=FALLING\n");
    scanf("%d", &value);

    if(value < NUM_EDGE_ENTRIES)
    {
        edge_trigger_data[40] = value;
    }
    else
    {
        printf("Out of range\n");
        return;
    }

    printf("0=TRIG_CPL_DC 1=TRIG_CPL_AC 2=TRIG_CPL_HF 3=TRIG_CPL_LF\n");
    scanf("%d", &value);

    if(value < NUM_TRIG_CPL_ENTRIES)
    {
        edge_trigger_data[13] = value;
    }
    else
    {
        printf("Out of range\n");
        return;
    }

    printf("0=TRIG_MODE_AUTO 1=TRIG_MODE_NORMAL 2=TRIG_MODE_ONCE\n");
    scanf("%d", &value);

    if(value < NUM_TRIG_MODE_ENTRIES)
    {
        edge_trigger_data[21] = value;
    }
    else
    {
        printf("Out of range\n");
        return;
    }

    printf("Enter Trigger Offset between -10000 and +10000\n");

    scanf("%d", &value);

    if( (value >= -10000) && (value <= 10000) )
    {
        edge_trigger_data[48] = (char) ((value >> 24) & 0x000000FF);
        edge_trigger_data[49] = (char) ((value >> 16) & 0x000000FF);
        edge_trigger_data[50] = (char) ((value >> 8) & 0x000000FF);
        edge_trigger_data[51] = (char) (value & 0x000000FF);

        printf("Send Trigger Opts Command\n");
        send_usb_data(edge_trigger_data, sizeof(edge_trigger_data));
    }
    else
    {
        printf("Value out of range!\n");
        return;
    }
}

void set_video_trigger(void)
{
    int value = 0;

    printf("0=CHANNEL_1 1=CHANNEL_2\n");
    scanf("%d", &value);

    if(value < NUM_CHANNEL_ENTRIES)
    {
        /* We dont know if we will use line mode or not. Best to update
           both messaages at the same time */

        video_trigger_data[10] = value;
        video_trigger_data[18] = value;
        video_trigger_data[26] = value;

        /* Line mode settings */
        video_trig_line_no_data[10] = value;
        video_trig_line_no_data[18] = value;
        video_trig_line_no_data[30] = value;
    }
    else
    {
            printf("Out of range\n");
            return;
    }

    printf("0=MODU_NTSC 1=MODU_PAL 2=MODU_SECAM\n");
    scanf("%d", &value);

    if(value < NUM_MODU_ENTRIES)
    {
        /* We dont know if we will use line mode or not. Best to update
           both messaages at the same time */
        video_trigger_data[13] = value;

        /* Line mode settings */
        video_trig_line_no_data[13] = value;
    }
    else
    {
            printf("Out of range\n");
            return;
    }

    printf("0=SYNC_LINE 1=SYNC_FIELD 2=SYNC_ODD 3=SYNC_EVEN 4=SYNC_LINE_NO\n");
    scanf("%d", &value);

    if(value < NUM_SYNC_ENTRIES)
    {
        if(value != SYNC_LINE_NO)
        {
            video_trigger_data[21] = value;
            printf("Send Video Trigger Command\n");
            send_usb_data(video_trigger_data, sizeof(video_trigger_data));
        }
        /*Line Number Mode. More options to set before send */
        else
        {
            if(video_trig_line_no_data[13] == MODU_NTSC)
            {
                printf("Select a Line Number between 1 and 525\n");
                scanf("%d", &value);

                if( (value < 0) || (value > 525) )
                {
                    /* Value out of range. Force Line 1 */
                    printf("Out of range\n");
                    return;
                }
            }
            else
            {
                printf("Select a Line Number between 1 and 625\n");
                scanf("%d", &value);

                if( (value < 0) || (value > 625) )
                {
                    /* Value out of range. Force Line 1 */
                    printf("Out of range\n");
                    return;
                }
            }

            /* Set the value before send */
            video_trig_line_no_data[22] = (char) ((value >> 24) & 0x000000FF);
            video_trig_line_no_data[23] = (char) ((value >> 16) & 0x000000FF);
            video_trig_line_no_data[24] = (char) ((value >> 8) & 0x000000FF);
            video_trig_line_no_data[25] = (char) (value & 0x000000FF);

            printf("Send Video LineNo Command\n");
            send_usb_data(video_trig_line_no_data, sizeof(video_trig_line_no_data));
        }
    }
    else
    {
        printf("Out of range\n");
        return;
    }
}

void send_autoset_command(void)
{
    printf("Send Autoset Command\n");
    send_usb_data(autoset_data, sizeof(autoset_data));
}


void send_self_cal_command(void)
{
    printf("Send Self Cal Command\n");
    send_usb_data(self_cal_data, sizeof(self_cal_data));
}

void send_factory_reset_command(void)
{
    printf("Send Factory Reset Command\n");
    send_usb_data(factory_reset_data, sizeof(factory_reset_data));
}
