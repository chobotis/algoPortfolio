///////////////////////////////////////////////////////////////////////////////
// maxtime.hh
//
// Compute the set of rides that maximizes the time spent at rides, within a given budget
// with the dynamic method or exhaustive search.
//
///////////////////////////////////////////////////////////////////////////////


#pragma once


#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <vector>


// One ride item available for purchase.
class RideItem
{
	//
	public:

		//
		RideItem
		(
			const std::string& description,
			size_t cost_dollars,
			double time_minutes
		)
			:
			_description(description),
			_cost_dollars(cost_dollars),
			_time_minutes(time_minutes)
		{
			assert(!description.empty());
			assert(cost_dollars > 0);
		}

		//
		const std::string& description() const { return _description; }
		int cost() const { return _cost_dollars; }
		double time() const { return _time_minutes; }

	//
	private:

		// Human-readable description of the ride, e.g. "new enchanted world". Must be non-empty.
		std::string _description;

		// Ride cost, in units of dollars; Must be positive
		int _cost_dollars;

		// Ride time in minutes; most be non-negative.
		double _time_minutes;
};


// Alias for a vector of shared pointers to RideItem objects.
typedef std::vector<std::shared_ptr<RideItem>> RideVector;


// Load all the valid ride items from the CSV database
// ride items that are missing fields, or have invalid values, are skipped.
// Returns nullptr on I/O error.
std::unique_ptr<RideVector> load_ride_database(const std::string& path)
{
	std::unique_ptr<RideVector> failure(nullptr);

	std::ifstream f(path);
	if (!f)
	{
		std::cout << "Failed to load ride database; Cannot open file: " << path << std::endl;
		return failure;
	}

	std::unique_ptr<RideVector> result(new RideVector);

	size_t line_number = 0;
	for (std::string line; std::getline(f, line); )
	{
		line_number++;

		// First line is a header row
		if ( line_number == 1 )
		{
			continue;
		}

		std::vector<std::string> fields;
		std::stringstream ss(line);

		for (std::string field; std::getline(ss, field, '^'); )
		{
			fields.push_back(field);
		}

		if (fields.size() != 3)
		{
			std::cout
				<< "Failed to load ride database: Invalid field count at line " << line_number << "; Want 3 but got " << fields.size() << std::endl
				<< "Line: " << line << std::endl
				;
			return failure;
		}

		std::string
			descr_field = fields[0],
			cost_dollars_field = fields[1],
			time_minutes_field = fields[2]
			;

		auto parse_dbl = [](const std::string& field, double& output)
		{
			std::stringstream ss(field);
			if ( ! ss )
			{
				return false;
			}

			ss >> output;

			return true;
		};

		std::string description(descr_field);
		double cost_dollars, time_minutes;
		if (
			parse_dbl(cost_dollars_field, cost_dollars)
			&& parse_dbl(time_minutes_field, time_minutes)
		)
		{
			result->push_back(
				std::shared_ptr<RideItem>(
					new RideItem(
						description,
						cost_dollars,
						time_minutes
					)
				)
			);
		}
	}

	f.close();

	return result;
}


// Convenience function to compute the total cost and time in a RideVector.
// Provide the RideVector as the first argument
// The next two arguments will return the cost and time back to the caller.
void sum_ride_vector
(
	const RideVector& rides,
	int& total_cost,
	double& total_time
)
{
	total_cost = total_time = 0;
	for (auto& ride : rides)
	{
		total_cost += ride->cost();
		total_time += ride->time();
	}
}


// Convenience function to print out each RideItem in a RideVector,
// followed by the total kilocalories and protein in it.
void print_ride_vector(const RideVector& rides)
{
	std::cout << "*** ride Vector ***" << std::endl;

	if ( rides.size() == 0 )
	{
		std::cout << "[empty ride list]" << std::endl;
	}
	else
	{
		for (auto& ride : rides)
		{
			std::cout
				<< "Ye olde " << ride->description()
				<< " ==> "
				<< "Cost of " << ride->cost() << " dollars"
				<< "; time = " << ride->time()
				<< std::endl
				;
		}

		int total_cost;
		double total_time;
		sum_ride_vector(rides, total_cost, total_time);
		std::cout
			<< "> Grand total cost: " << total_cost << " dollars" << std::endl
			<< "> Grand total time: " << total_time
			<< std::endl
			;
	}
}


// Convenience function to print out a 2D cache, composed of a std::vector<std::vector<double>>
// For sanity, will refuse to print a cache that is too large.
// Hint: When running this program, you can redirect stdout to a file,
//	which may be easier to view and inspect than a terminal
void print_2d_cache(const std::vector<std::vector<double>>& cache)
{
	std::cout << "*** 2D Cache ***" << std::endl;

	if ( cache.size() == 0 )
	{
		std::cout << "[empty]" << std::endl;
	}
	else if ( cache.size() > 250 || cache[1].size() > 250 )
	{
		std::cout << "[too large]" << std::endl;
	}
	else
	{
		for ( const std::vector<double>& row : cache)
		{
			for ( double value : row )
			{
				std::cout << std::setw(5) << value;
			}
			std::cout << std::endl;
		}
	}
}

// Filter the vector source, i.e. create and return a new RideVector containing the subset of 
// the ride items in source that match given criteria.
// This is intended to:
//	1) filter out ride with zero or negative time that are irrelevant to our optimization
//	2) limit the size of inputs to the exhaustive search algorithm since it will probably be slow.
//
// Each ride item that is included must have at minimum min_time and at most max_time.
//	(i.e., each included ride item's time must be between min_time and max_time (inclusive).
//
// In addition, the the vector includes only the first total_size ride items that match these criteria.
std::unique_ptr<RideVector> filter_ride_vector
(
	const RideVector& source,
	double min_time,
	double max_time,
	int total_size
)
{
	std::unique_ptr<RideVector> nuVector(new RideVector);
	for (auto& ride : source){
		if (nuVector->size() < total_size){
			if (ride->time() >= min_time && ride->time() < max_time){
				nuVector->push_back(ride);
			}
		}
	}
	return nuVector;

}

int max(int x, int y)
{
    return (x > y) ? x : y;
}
// Compute the optimal set of ride items with a dynamic algorithm.
// Specifically, among the ride items that fit within a total_cost budget,
// choose the selection of rides whose time is greatest.
// Repeat until no more ride items can be chosen, either because we've run out of ride items,
// or run out of dollars.
std::unique_ptr<RideVector> dynamic_max_time
(
	const RideVector& rides,
	int total_cost
)
{
	std::unique_ptr<RideVector> output(new RideVector);
   // TODO: implement this function, then delete the return statement below
   std::vector<double> vecTime;
   std::vector<int> vecCost;
   for (int i = 0; i < rides.size(); i++){
	   vecTime.push_back(rides[i]->time());
	   vecCost.push_back(rides[i]->cost());
   }
   int cache_x = rides.size();
   std::vector<std::vector<int>> cache(cache_x + 1, std::vector<int> (total_cost + 1));
   for (int x = 0; x <= cache_x; x++){
	   for (int y = 0; y <= total_cost; y++){
		   if (x == 0 || y == 0){
			   cache[x][y] = 0;
		   }
		   else if (vecCost[x - 1] <= y){
			   cache[x][y] = max(vecTime[x - 1] + cache[x - 1][y - vecCost[x - 1]], cache[x - 1][y]);
		   }
		   else{
			   cache[x][y] = cache[x - 1][y];
		   }
	   }
   }


   int cache_result = cache[cache_x][total_cost];
   int cost = total_cost;
   for (int z = cache_x; z > 0 && cache_result > 0; z--){
	   if (cache_result == cache[z - 1][cost]){
		   continue;
	   }
	   else{
		   cache_result -= vecTime[z - 1];
			cost -= vecCost[z - 1];
			output->push_back(rides[z - 1]);
	   }
   }

	return output;
}

std::vector<std::vector<RideItem>> getTimeSubsets(std::vector<RideItem> source)
{
    std::vector<std::vector<RideItem>> subset, subTemp;

    std::vector<RideItem> temp;
    subset.push_back(temp);

    for(int i = 0; i < source.size(); i++)
    {
        subTemp = subset;
        for(int j = 0; j < subTemp.size(); j++){subTemp[j].push_back(source[i]);}
        for(int k = 0; k < subTemp.size(); k++){subset.push_back(subTemp[k]);}
    }
    return subset;
}

// Compute the optimal set of ride items with a exhaustive search algorithm.
// Specifically, among all subsets of ride items,
// return the subset whose dollars cost fits within the total_cost budget,
// and whose total time is greatest.
// To avoid overflow, the size of the ride items vector must be less than 64.
std::unique_ptr<RideVector> exhaustive_max_time
(
	const RideVector& rides,
	double total_cost
)
{
	std::unique_ptr<RideVector> output(new RideVector);
	RideVector best;
	double best_cost = 0;
	double best_time = 0;
	unsigned int bit_length = pow(2, rides.size());	//bit_length = 2^n - 1
	for (int i = 0; i < bit_length; i++){			//for 
		RideVector subsets;					//Initialize subsets vector at every iteration
		double subset_cost = 0;				// Initialize subset_cost at every iteration
		double subset_time = 0;
		for (int j = 0; j < rides.size(); ++j){
			if ((i >> j) & 1){
				subsets.push_back(rides[j]);
				subset_cost += rides[j]->cost();
				subset_time += rides[j]->time();
			}
		}
		if (subset_cost <= total_cost){
			if (best.empty() || (subset_time > best_time)){
				best = std::move(subsets);
				best_cost = subset_cost;
				best_time = subset_time;
			}
		}
		subsets.clear();					
	}
	for (int i = 0; i < best.size(); ++i){
		output->push_back(best[i]);
	}
	return output;
}









