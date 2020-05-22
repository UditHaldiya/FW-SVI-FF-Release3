#ifndef TIME_DEFS_H_
#define TIME_DEFS_H_

#ifdef NDEBUG
#define TIME_INSECOND_ONEHOUR    (60*60)
#else //for accelerated testing!
#define TIME_INSECOND_ONEHOUR    seconds_in_hour
extern u16_least seconds_in_hour;
#endif //NDEBUG


#define TIME_INSECOND_ONEDAY     (24*TIME_INSECOND_ONEHOUR)
#define TIME_INSECOND_ONEWEEK    (7*TIME_INSECOND_ONEDAY)
#define TIME_INSECOND_ONEMONTH   (30*TIME_INSECOND_ONEDAY)
#define TIME_INSECOND_ONEYEAR    (12*TIME_INSECOND_ONEMONTH)

#define NUMBER_OF_MS_IN_SECOND          (1000u)
#define NUMBER_OF_MS_IN_MINUTE         (NUMBER_OF_MS_IN_SECOND*60U)
#define MS_TO_SEC(x)                    ((x) / NUMBER_OF_MS_IN_SECOND)

#endif //TIME_DEFS_H_
