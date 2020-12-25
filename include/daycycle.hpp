
#ifndef DAYCYCLE_H
#define DAYCYCLE_H

class DayCycle {
   private:
    int awakeTime;
    int asleepTime;
    int progress;

   public:
    DayCycle(int = 0, int = 0);
    int getDayTime() const;
    int getNightTime() const;
    int getProgress() const;
    int getCycles() const;

    void setDayTime(int);
    void setNightTime(int);
    void setProgress(int);

    DayCycle& operator++();
    DayCycle operator++(int);
    DayCycle& operator+=(int);
};

#endif