#include<bits/stdc++.h>
#include<conio.h>
#define kmax 15
using namespace std;

typedef struct
{
    int data;
    int destination;
    int stn_no;
} frame;
frame frames[7];

int tt[10]= {0},k=1,t=1,ns1=0,ns=0,mark1=0,mark2=0;
int mark[10]= {0},l[10]= {0},ii[10]= {0},last_i=0;
float t_fr = 0.0;
int channel[15]= {0};
int pp[10]= {0},last_d=0;
void transmission_data();
void wait()
{
    unsigned long long int lli=300000000,y;
    for(y=0; y<lli; y++)
    {
        ///hello
    }
}
void mwait()
{
    unsigned long long int lli=700000000,y;
    for(y=0; y<lli; y++)
    {
        ///hello
    }
    wait();
}
void print()
{

    system("cls");
    cout<<endl<<endl<<endl<<endl;
    cout<<"            S1      S2      S3      S4     S5"<<endl;
    cout<<"            ";
    for(int i = 1; i<=5; i++)
    {
        cout<<channel[i]<<"       ";

        if(channel[i]==-1)
        {
            channel[i]=0;
        }
    }
    cout<<endl;
    wait();
}
int p_persistence(int i)
{
    if(channel[i]!=0)
    {
        return 0;
    }
    else
    {
        float p=0.5;

        float r=float(rand()%11)/10.0;

        if(r<=p)
        {
            ii[i]=1;

            return 1;
        }
        else
        {

            return 0;
        }
    }
}
void back_off(int st_no)
{
    pp[st_no]=0;
    if(k>kmax)
    {
        cout<<"Transmission from "<<st_no<<" is aborted."<<endl;
        mwait();
        tt[st_no]=0;
        ns1++;
    }
    else
    {
        int s=pow(2,k)-1;
        int r=(rand()%s);
        tt[st_no]+=r*t_fr;
        k++;

        ii[st_no]=0;
        l[st_no]=0;
    }
    mark1 = 0;
}

void transmit(int stn)
{

    int station = frames[stn].stn_no;
    int data = frames[stn].data;
    int destination = frames[stn].destination;

    if(l[stn] == 0 && channel[stn]==0)
    {
        channel[stn]= data; ///loading channel
        l[stn] =stn;
    }
    else if(stn>destination )
    {
        int i=--l[stn];
        if(channel[i]!=0)
        {
            mark1=1;
            channel[i]=-1;

            channel[i+1]=0;
            print();
            cout<<"collision detected at  station "<<i<<endl;
            mwait();

            cout<<endl<<endl<<"Resending data";
            for(int i = 0;i<2;i++){
                for(int j = 0;j<=i;j++)
                   {

                       cout<<".";
                       wait();
                   }

            }
            cout<<endl;
            back_off(stn);
            int kl,j;
            for(j=1; j<6; j++)
            {
                if(j!=stn && i==l[j])
                    kl=j;
            }
            back_off(kl);
//            cout<<kl;
//            getch();
        }
        else
        {
            channel[i] = channel[i+1];
            channel[i+1]=0;


            if(i==destination)
            {
                ns1++;
                mark[stn] = 1;
                last_i = stn;

            }
        }
    }
    else if(stn<destination )
    {
        int i = ++l[stn];

        if(channel[i]!=0)
        {

            mark1=1;
            channel[i]=-1;
            channel[i-1]=0;
            print();
            cout<<"collision detected at "<<i<<" station."<<endl;
            mwait();
            cout<<endl<<endl<<"Resending data";
            for(int i = 0;i<2;i++){
                     for(int j = 0;j<=i;j++)
                   {

                       cout<<".";

                       wait();
                   }


            }

            cout<<endl;
            back_off(stn);
            int kl,j;
            for(j=1; j<6; j++)
            {
                if(j!=stn && i==l[j])
                    kl=j;
            }
            back_off(kl);
//            cout<<kl;
//            getch();
        }
        else
        {
            channel[i] = channel[i-1];
            channel[i-1] = 0;
            if(i==destination)
            {
                ns1++;
                mark[stn] = 1;
                last_i = stn;

            }
        }
    }
}


void transmission_data()
{

    while(1)
    {
        if(t == tt[1])
        {

            if(ii[1] == 0 && p_persistence(1))
            {

                    pp[1]=1;
                    transmit(1);

            }
            else if(pp[1])
            {
                transmit(1);
            }
            tt[1]++;

        }
        if(t == tt[2])
        {
            if(ii[2] == 0 && p_persistence(2))
            {

                    pp[2]=1;
                    transmit(2);

            }
            else if(pp[2])
            {
                transmit(2);
            }


            tt[2]++;

        }
        if(t == tt[3])
        {
            if(ii[3] == 0 && p_persistence(3) )
            {

                    pp[3]=1;
                    transmit(3);

            }
            else if(pp[3])
            {
                transmit(3);
            }

            tt[3]++;

        }
        if(t == tt[4])
        {
            if(ii[4] == 0 && p_persistence(4))
            {

                    pp[4]=1;
                    transmit(4);

            }
            else if(pp[4])
            {
                transmit(4);
            }

            tt[4]++;

        }
        if(t == tt[5])
        {
            if(ii[5] == 0 && p_persistence(5))
            {

                    pp[5]=1;
                    transmit(5);

            }
            else if(pp[5])
            {
                transmit(5);
            }

            tt[5]++;

        }
        print();

        if(mark[last_i] == 1)
        {
            channel[frames[last_i].destination]=0;
            tt[last_i]=0;
            cout<<"success from station "<<last_i<<endl;

            mwait();
            print();
            last_i=0;
        }
        if(ns == ns1)
        {
            cout<<endl<<"          ";
            cout<<"All data processing done."<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
            getch();
            exit(0);
        }
        t++;
    }
}

int main()
{
    char ch;
    int des,fno;
    srand ( time(NULL) );
    for(int i=1; i<6; i++)
    {
        cout<<"\nIs station "<<i<<" sending data?(y/n)";
        cin>>ch;
        if(ch=='y'|| ch=='Y')
        {
            ns++;
            cout<<"\nEnter the time to start transmit : ";
            cin>>tt[i];
            cout<<"\nEnter the destination station : ";
            cin>>frames[i].destination;
            cout<<"\nEnter  data to be sent : ";
            cin>>frames[i].data;
            frames[i].stn_no=i;
        }

    }

    int cnt = 0;
    int avg;
    for(int i = 1; i<=5; i++)
    {
        if(tt[i]!= 0)
        {
            avg+=tt[i];
            cnt++;
        }
    }
    t_fr= float(avg)/float(cnt);
    transmission_data();

    return 0;

}
