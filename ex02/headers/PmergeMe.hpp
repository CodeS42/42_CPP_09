#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <cstring>
# include <algorithm>
# include <vector>
# include <deque>
# include <cctype>
# include <cstddef>
# include <cstdlib>
# include <limits>
# include <ctime>

template<typename T>
class PmergeMe
{
	private:
		enum Input
		{
			INVALID_INPUT,
			VALID_INPUT
		};

		PmergeMe() {}

		PmergeMe(const PmergeMe& obj)
		{
			(void)obj;
		}

		PmergeMe& operator=(const PmergeMe& other)
		{
			(void)other;
			return (*this);
		}

	public:
		~PmergeMe() {}

		static std::string concatenateStrings(int ac, char* av[])
		{
			std::string input = av[1];

			for (int i = 2 ; i < ac ; i++)
			{
				input += ' ';
				input += av[i];
			}
			return (input);
		}

		static int fillContainer(T& container, std::string& input)
		{
			std::size_t i, count_nbs, size = input.size();
			const char* nb_str;
			long nb;
			
			for (i = 0 ; i < size ; i++)
			{
				if (!isspace(input[i]))
				{
					if (!isdigit(input[i]))
						return (INVALID_INPUT);
					count_nbs = i;
					while (input[count_nbs] && isdigit(input[count_nbs]))
						count_nbs++;
					nb_str = input.substr(i, count_nbs - i).c_str();
					nb = std::strtol(nb_str, NULL, 10);
					if (nb < std::numeric_limits<int>::min() || nb > std::numeric_limits<int>::max())
						return (INVALID_INPUT);
					container.push_back(atoi(nb_str));
					i = count_nbs - 1;
				}
			}
			if (container.size() < 2 || duplicates(container))
				return (INVALID_INPUT);
			return (VALID_INPUT);
		}

		static bool duplicates(T& container)
		{
			typename T::iterator it, ite;
			
			for (it = container.begin() ; it != container.end() - 1 ; it++)
			{
				for (ite = it + 1 ; ite != container.end() ; ite++)
				{
					if (*it == *ite)
						return (true);
				}
			}
			return (false);
		}

		static bool isSorted(T& container)
		{
			typename T::iterator it1, it2;

			for (it1 = container.begin() ; it1 != container.end() - 1 ; it1++)
			{
				for (it2 = it1 + 1 ; it2 != container.end(); it2++)
				{
					if (*it1 > *it2)
						return (false);
				}
			}
			return (true);
		}

		static void displayContainer(T& container)
		{
			typename T::iterator it;
			
			for (it = container.begin() ; it != container.end() ; it++)
				std::cout << *it << " ";
			std::cout << std::endl;
		}

		static void sortNumbers(T& container)
		{
			typename T::iterator it;
			T largest_nbs;
			T smallest_nbs;

			if (container.size() < 2)
				return;

			for (it = container.begin() ; it != container.end() ; it += 2)
			{
				if (it == container.end() - 1)
				{
					smallest_nbs.push_back(*it);
					break;
				}
				else if (*it > *(it + 1))
				{
					largest_nbs.push_back(*it);
					smallest_nbs.push_back(*(it + 1));
				}
				else
				{
					largest_nbs.push_back(*(it + 1));
					smallest_nbs.push_back(*it);
				}
				if (it == container.end() - 2)
					break;
			}

			sortNumbers(largest_nbs);

			for (it = smallest_nbs.begin() ; it != smallest_nbs.end() ; it++)
			{
				std::size_t start = 0, end = largest_nbs.size(), mid;

				while (end > start)
				{
					mid = (start + end) / 2;
					if (*it < largest_nbs[mid])
						end = mid;
					else if (*it > largest_nbs[mid])
						start = mid + 1;
				}
				largest_nbs.insert(largest_nbs.begin() + start, *it);
			}
			container = largest_nbs;
		}
};

typedef PmergeMe<std::vector<int> > PmergeMeVector;
typedef PmergeMe<std::deque<int> > PmergeMeDeque;

#endif
