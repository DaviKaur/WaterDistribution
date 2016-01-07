// Pipes_app.cpp
// models a water supply system

//#include "Pipes.h"				// pipes header file
#include "Pipes.cpp"

int main()
  {
	char ch ='a';
	Source src=(100);			// source (maximum capacity)
	Pipe pipe1(80);				// pipe (resistance)
	Valve valve1(on);			// valve (initially on)

	Tank tank1(60);				// tank1 (maximum outflow)
	Switch switch1(&tank1, 300);		// tank1 high switch
	Switch switch2(&tank1, 50);		// tank1 low switch

	Pipe pipe2(80);				// pipe
	Sink sink1(30);				// sink (maximum capacity)
	Pipe pipe3(40);				// pipe
	Valve valve2(on);			// valve

	Tank tank2(80);				// tank2
	Switch switch3(&tank2, 250);		// tank2 high switch
	Switch switch4(&tank2, 50);		// tank2 low switch

	Sink sink2(20);				// sink

	cout<<"Press Enter for new time tick, 'x' to exit\n";
	while(ch != 'x')			// quit on 'x' key
	  {					// make connections
		src >= pipe1;			// source flows into pipe1
		pipe1 >= valve1;		// pipe1 flows into valve1
		valve1 >= tank1;		// valve1 flows into tank1
		Tee(tank1, pipe2, pipe3);	// output of tank1 splits
		pipe2 >= sink1;			// pipe2 flows into sink1
		pipe3 >= valve2;		// pipe3 flows into valve2
		valve2 >= tank2;		// valve2 flows into tank2
		tank2 >= sink2;			// tank2 flows into sink2

		src.Tick();			// update all components
		pipe1.Tick();			// and switches
		valve1.Tick();
		tank1.Tick();
		switch1.Tick();
		switch2.Tick();
		pipe2.Tick();
		sink1.Tick();
		pipe3.Tick();
		valve2.Tick();
		tank2.Tick();
		switch3.Tick();
		switch4.Tick();
		sink2.Tick();
						// if tank1 gets too high
		if (valve1.Status() == on && switch1.Status() == on)
			valve1.Status() = off;
						// if tank1 gets too low
		if (valve1.Status() == off && switch2.Status() == off)
			valve1.Status() = on;
						// if tank2 gets too high
		if (valve2.Status() == on && switch3.Status() == on)
			valve2.Status() = off;
						// if tank2 gets too low
		if (valve2.Status() == off && switch4.Status() == off)
			valve2.Status() = on;
						// output
		cout << "Src=" << setw(2) << src.Flow();
		cout << "P1=" << setw(2) << pipe1.Flow();
		if (valve1.Status() == off)
			cout << "V1 = off";
		else
			cout << "V1 = on";
		cout << "T1=" << setw(3) << tank1.Contents();
		cout << "P2=" << setw(2) << pipe2.Flow();
		cout << "Snk1=" << setw(2) << sink1.Flow();
		cout << "P3=" << setw(2) << pipe3.Flow();
		if (valve2.Status() == off)
			cout << "V2 = off";
		else
			cout << "V2 = on";
		cout << "T2=" << setw(3) << tank2.Contents();
		cout << "Snk2=" << setw(2) << sink2.Flow();
//		ch = getch();
		cout << '\n';
		}				// end while
		return ch;
	}					// end main()
						
