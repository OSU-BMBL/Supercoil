#include "valleyDetect.h"

/*detect the valleys from the expression signals*/
int detect_peak(
        const double*   data, /* the data */
        int             data_count, /* row count of data */
        int*            emi_peaks, /* emission peaks will be put here */
        int*            num_emi_peaks, /* number of emission peaks found */
        int             max_emi_peaks, /* maximum number of emission peaks */
        int*            absop_peaks, /* absorption peaks will be put here */
        int*            num_absop_peaks, /* number of absorption peaks found */
        int             max_absop_peaks, /* maximum number of absorption peaks */
        double          delta, /* delta used for distinguishing peaks */
        int             emi_first /* should we search emission peak first of absorption peak first? */
        )
{
    int     i;
    double  mx;
    double  mn;
    int     mx_pos = 0;
    int     mn_pos = 0;
    int     is_detecting_emi = emi_first;

    mx = data[0];
    mn = data[0];

    *num_emi_peaks = 0;
    *num_absop_peaks = 0;

    for(i = 1; i < data_count; ++i)
    {
        if(data[i] > mx)
        {
            mx_pos = i;
            mx = data[i];
        }
        if(data[i] < mn)
        {
            mn_pos = i;
            mn = data[i];
        }
	/*printf ("%.2f\t%.2f\t%.2f\t%.2f\t%d\t%d\n", mx,mn, delta, data[i], i, data_count);*/
        if(is_detecting_emi && data[i] < MAX(mx - delta,mx/2))
        {
            if(*num_emi_peaks >= max_emi_peaks) /* not enough spaces */
                return 1;

            emi_peaks[*num_emi_peaks] = mx_pos;
            ++ (*num_emi_peaks);

            is_detecting_emi = 0;

            i = mx_pos - 1;

            mn = data[mx_pos];
            mn_pos = mx_pos;
        }
        else if((!is_detecting_emi) && data[i] > MIN(mn + delta, 2*mn))
        {
            if(*num_absop_peaks >= max_absop_peaks)
                return 2;

            absop_peaks[*num_absop_peaks] = mn_pos;
            ++ (*num_absop_peaks);

            is_detecting_emi = 1;
            
            i = mn_pos - 1;

            mx = data[mn_pos];
            mx_pos = data[mn_pos];
        }
    }
    return 0;
}

