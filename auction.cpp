#include<iostream>
#include <vector>
using namespace std;



class bid
{
public:
	int bidded_val;
	string owner;
};
class item
{
public:
	string name;
	int min_bid;
	int max_bid;
	bool issold;
	string owner;
			

	item(string name1, int min_bid1, int max_bid1, string owner1)
	{
		name = name1;
		min_bid = min_bid1;
		max_bid = max_bid1;
		issold = false;
		owner = owner1;
	}
};

class seller
{
public:
	string name;
	vector <item> list_of_item;
};


class buyer
{
public:
	string name;
	vector <item> items_bought;
};

class auction
{
public:
	string item_name;
	bool isactive;
	vector <bid> list_of_bids;

};

vector <seller> sellerslist;
vector <buyer> buyerlist;
vector <item> itemlist;
vector <auction> auctionlist;

void createauction(string name)
{
	auction a;
	a.item_name = name;
	a.isactive = true;
	auctionlist.push_back(a);
}


void createseller(string name, vector<item> items) {
	seller s;
	s.name = name;
	for (item i : items) {
		s.list_of_item.push_back(i);
	}

	sellerslist.push_back(s);

}

void createbuyer(string name)
{
	buyer b;
	b.name = name;
	buyerlist.push_back(b);
}

void bidding(string name, string buyer_name, int bid_val)
{
	for (item i : itemlist) {
		if (i.name == name) {
			if (i.max_bid< bid_val || i.min_bid > bid_val) {
				return;
			}
		}
	}
	bid b;
	b.bidded_val = bid_val;
	b.owner = buyer_name;
	for (int i = 0; i< auctionlist.size(); i++)
	{
		if (auctionlist[i].item_name == name)
		{
			auctionlist[i].list_of_bids.push_back(b);
			break;
		}
	}
}

void updatebid(string item_name, string bidder_name, int updated_bid_val)
{
	for (item i : itemlist) {
		if (i.name == item_name) {
			if (i.max_bid< updated_bid_val || i.min_bid > updated_bid_val) {
				return;
			}
		}
	}
	
	for (int i = 0; i < auctionlist.size(); i++)
	{
		if (auctionlist[i].item_name == item_name)
		{
			for (int j = 0; j<auctionlist[i].list_of_bids.size(); j++) 
			{
				if (auctionlist[i].list_of_bids[j].owner == bidder_name)
				{
					auctionlist[i].list_of_bids[j].bidded_val = updated_bid_val;
				}
			}
		}
	}
}


void withdraw(string item_name, string bidder_name)
{
	for (int ii = 0; ii < auctionlist.size(); ii++)
	{
		if (auctionlist[ii].item_name == item_name)
		{
			for (auto i = auctionlist[ii].list_of_bids.begin(); 
				i != auctionlist[ii].list_of_bids.end() ; i ++ )
			{
				if ((*i).owner == bidder_name)
				{
					auctionlist[ii].list_of_bids.erase(i);
					int x = 10;
					break;
				}
			}
			break;
		}
	}
}



string closeauction(string item_name)
{
	string winner;
	int max = 0;
	for (auction ai : auctionlist)
	{
		if (ai.item_name == item_name)
		{
			ai.isactive = false;
			for (auto i = ai.list_of_bids.begin(); i != ai.list_of_bids.end(); i++)
			{
				if ((*i).bidded_val > max)
				{
					max = (*i).bidded_val;
					winner = (*i).owner;
					
				}
			}
		}
	}
	return winner;
}

void printbid(string item_name)
{
	for (auction ai : auctionlist)
	{
		if (ai.item_name == item_name)
		{
			for (auto i = ai.list_of_bids.begin(); i != ai.list_of_bids.end(); i++)
			{
				cout << (*i).bidded_val << " => " <<(*i).owner << endl;

			}
		}
	}
}

int main()
{
	//Driver
	vector<item> items;

	item a("a", 10, 50, "s1"); 
	item b("b",0,20,"s1"); 

	items.push_back(a);
	items.push_back(b);
	createseller("s1", items);


	item c("c",20,100,"s2"); 
	item d("d",50,100,"s2"); 

	itemlist.push_back(a);
	itemlist.push_back(b);
	itemlist.push_back(c);
	itemlist.push_back(d);

	items.clear();
	items.push_back(c);
	items.push_back(d);
	createseller("s2", items);

	createbuyer("b1");
	createbuyer("b2");
	createbuyer("b3");


	createauction("a");
	createauction("b");
	createauction("c");

	//bidding("a", "b1", 20);
	bidding("c", "b1", 20);
	bidding("c", "b2", 35);
	
	updatebid("c", "b1", 25);
	updatebid("c", "b1", 40);
	updatebid("c", "b2", 50);
	updatebid("c", "b2", 5000);
	updatebid("c", "b2", 60);
	withdraw("c", "b2");

	printbid("c");

	string winner = closeauction("c");
	cout << "winner is " << winner << endl;

	cout << "IAMDONE";
}

