#include <iostream>
#include <vector>
class IIterator
{
public:
	virtual std::string FirstItem() = 0;
	virtual std::string NextItem() = 0;
	virtual std::string CurrentItem() = 0;
	virtual bool IsDone() = 0;		
};

class IAggregate
{
public:
	virtual IIterator* GetIterator() = 0;
	virtual std::string& operator[](int itemIndex) = 0;
    virtual int Count() = 0;
};


class MyIterator : public IIterator
{
	IAggregate *aggregate_;
    int currentIndex_;

public:
	MyIterator(IAggregate *aggregate)
		: currentIndex_(0)
		, aggregate_(aggregate)
	{
		
	}
	
	std::string FirstItem()
	{
		 currentIndex_ = 0;
         return (*aggregate_)[currentIndex_];
	}
	
	std::string NextItem()
	{
		currentIndex_ += 1;

        if (IsDone() == false)
        {
            return (*aggregate_)[currentIndex_];
        }
        else
        {
            return "";
        }
	}

	std::string CurrentItem()
	{
		return (*aggregate_)[currentIndex_];
	}

	bool IsDone()
	{
		if (currentIndex_ < aggregate_->Count())
        {
            return false;
        }
        return true;
	}

};
class MyAggregate : public IAggregate
{
	std::vector<std::string> values_;

public:
	MyAggregate(void)	
	{}

	//Helper function to populate the collection
	void AddValue(std::string value)
	{
		values_.push_back(value);
	}

	IIterator* GetIterator()
	{
		IIterator *iter = new MyIterator(this); 
		return iter;
	}

	std::string& operator[](int itemIndex)
	{
		return values_[itemIndex];
	}	

    int Count()
	{
		return values_.size();
	}
};

int main(int argc, char* argv[])
{
	MyAggregate aggr;

    aggr.AddValue("1");
    aggr.AddValue("2");
    aggr.AddValue("3");
    aggr.AddValue("4");
    aggr.AddValue("5");
    aggr.AddValue("6");
    aggr.AddValue("7");
    aggr.AddValue("8");
    aggr.AddValue("9");
    aggr.AddValue("10");

    IIterator *iter = aggr.GetIterator();

	for (std::string s = iter->FirstItem(); iter->IsDone() == false;  s = iter->NextItem())
    {
		std::cout << s.c_str() << std::endl;
    }

	return 0;
}