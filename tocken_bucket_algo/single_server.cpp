#include<iostream>
#include<ctime>
#include<chrono>
#include<thread>
using namespace std;


/*class Tockenbucket{
    private:

    int capacity;
    double bucket;
    double refillrate;
    long long lastfilltime;

    public: 

    Tockenbucket(int cap,double rate ):capacity(cap),bucket(cap),refillrate(rate)
    {
           lastfilltime=time(nullptr);
    }

    bool allowreq(){

    }
}*/





class TokenBucket {
private:
    int capacity;
    double tokens;
    double refillRate;
    long long lastRefillTime;

public:
    TokenBucket(int cap, double rate)
        : capacity(cap),
          tokens(cap),
          refillRate(rate)
    {
        lastRefillTime = time(nullptr);
    }

    bool allowRequest() {
        long long now = time(nullptr);

        double elapsed = now - lastRefillTime;

        tokens = min(
            (double)capacity,
            tokens + elapsed * refillRate
        );

        lastRefillTime = now;

        if(tokens >= 1) {
            tokens--;
            return true;
        }

        return false;
    }
};

int main() {

    TokenBucket bucket(5,1);

    for(int i=1;i<=7;i++)
    {
        if(bucket.allowRequest())
            cout<<"Request "<<i<<" Allowed\n";
        else
            cout<<"Request "<<i<<" Blocked\n";
    }

    cout<<"\nWaiting 3 seconds...\n";

    this_thread::sleep_for(
        chrono::seconds(3)
    );

    if(bucket.allowRequest())
        cout<<"New Request Allowed\n";
    else
        cout<<"New Request Blocked\n";


        return 0;
        
}