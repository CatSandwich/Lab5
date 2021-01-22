#include "JInclude.h"
#include "CalculatedValue.h"

#include "OnAction.h"
#include "OnPlay.h"
#include "OnShop.h"

using namespace Events;

/*

	There's a lot left in this I would like to add/refactor but at this point I'm losing interest so I won't make many more changes.

	A few of my classes are a bit messy since I didn't get to refactor all of them. At the start I was writing C#-esque code. Everything was a header file.
	Some classes still are. A few of the classes I was forced to split into definition and implementation since there were circular dependencies. Notably the FirstTry upgrade.
	I definitely wrote this program similarly to the game I'm currently working on so the structure isn't the most optimal for a linear game as we talked about but
	it was good practice.

	The basic program structure is:
	
	Three events:
	- OnAction: Allows the user to select Play, Shop, Quit. Quit exits the game where the other two call the next two events.
	- OnPlay  : Runs the guessing game and modifies stats afterwards.
	- OnShop  : Displays the shop and allows the user to purchase upgrades.
	
	The events are structured as multiple function pointers. Most are set in the event constructors, but some are modified at runtime such as PostGameFirstTry which
	is set through buying an upgrade. They're ordered in a std::map by way of enums passed in as a generic on class definition. I used a map so I can easily modify
	the callbacks at runtime by simply calling Event::SetCallback(enum value, lambda expression).

	The event manager was intended to be a singleton but it's improperly formatted. Since I only declare one it's not a problem, but the point of a singleton is for
	safety if another is accidentally created. Stats and event manager are singletons which I'm not as happy about. I would prefer to not use them as static but it felt
	cleaner this way. It also was the only way to resolve the circular dependency between the stats and the events. If I declared the stats first, it would reference callbacks
	that didn't exist yet, and if I declared them after, the events were referencing null stats. By using a static instance of stats it solved that problem but it feels hacky.

	The upgrades are set up the way I like settings things like that up. I made the shared functionality in the base class so that making a new upgrade was as simple as setting
	the values of the names, descriptions, costs, and callbacks. The upgrade callbacks are the code that's run to insert their functionality into the codebase - whether it's
	actually setting event callbacks or modifying stats. It's clean and probably the part I'm proudest of although it's not a new concept to me.

	Here are where all of the requirements are met:

	Including libraries - I have one or two...
	Variables			- I think I'm good on that front
	Operators		    
		Assignments		- Got a few in here
		Modulus			- Limiting the guessing game max, kind of a repeat of a previous lab but there are only so many ways to use modulus
		++				- Got a few for loops around, using += to add to creds 
	Comments			- I'll be going through commenting things. I tend to refactor things to read like english already so I use comments for parts that always look bad
	Prompts				- See OnAction ShowChoices callback, OnPlay GameLoop callback or OnShop GetInput. Mostly done through J::Read function.
	Input/Output		- Hand in hand with prompts. Got a lot of console in/out
	Random values		- See OnPlay GameLoop for my random generation
		Seeded properly - First line of the main function below
	If statements		- All over the place
		&&				- I don't seem to have one at the time of writing; I added one in the main function below
		||				- Same deal; I'll add one into the main function
	For loop			- Assuming I have these all over. Theres on in the event functionality to call callbacks. Same deal for CalculatedValue
	While loop			- One in the main function, also used for input validation

	(1)Sentinel values	- I'm using the OnAction result boolean as a sentinel value to exit
	(2)Loop continue	- In the shop display builder, it iterates through upgrades and uses continue to ignore max level upgrades
	(3)Assignments		- += in OnPlay to award credits
	(4)Switch statement	- OnAction switches on input
	(5)Enum				- Events use enums to order callbacks

*/

int main()
{
	srand(time(0));
	EventManagerType events;
	OnAction onAction (EventList::OnAction);
	OnPlay   onPlay   (EventList::OnPlay  );
	OnShop   onShop   (EventList::OnShop  );
	Stats stats(1000);

	std::string input;
	std::cout << "Would you like to play a game? (y/n): ";
	std::cin >> input;

	while (!onAction.Result && (input == "y" || input == "yes"))
	{
		onAction.Run();
	}
}