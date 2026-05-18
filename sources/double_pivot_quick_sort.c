/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_pivot_quick_sort.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:00:32 by ykadosh           #+#    #+#             */
/*   Updated: 2025/03/05 12:08:38 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		median_of_three(int *a, int *b, int *c);
static void		pick_furthest_pivot(int median, int *b, int *c);
static uint8_t	sort_and_partition(int *array, size_t *l_pvt, size_t *r_pvt);
static void		swap_and_move(int *array, size_t i, size_t pvt);

/*
* This double_pivot_quick_sort() function accepts integer arrays, and sorts
* them in ascending order, without using any malloc() call: all of the swapping
* and memory movement is done within the bounds of the given integer array.
* This implementation is using a median of three strategy for optimizing the
* choice of the pivots, when the array (or its subarrays, in the context of the
* recursive calls) contain/s more than 20 elements.
* NOTE: If there are any duplicated integers within the array, the sorting
* process stops, duplicate_flag is updated to be true and it is returned.
*/
uint8_t	double_pivot_quick_sort(int *array, size_t n)
{
	size_t	l_pivot;
	size_t	r_pivot;
	uint8_t	duplicate_flag;

	l_pivot = 0;
	r_pivot = n - 1;
	duplicate_flag = 0;
	if (n > 20)
		median_of_three(&array[0], &array[(n - 1) / 2], &array[n - 1]);
	else if (array[0] > array[n - 1])
		ft_swap(&array[0], &array[n - 1]);
	duplicate_flag += sort_and_partition(array, &l_pivot, &r_pivot);
	if (duplicate_flag)
		return (duplicate_flag);
	if (l_pivot > 1)
		duplicate_flag += double_pivot_quick_sort(array, l_pivot);
	if (r_pivot > l_pivot + 2)
		duplicate_flag += double_pivot_quick_sort(&array[l_pivot + 1],
				r_pivot - l_pivot - 1);
	if (n > r_pivot + 2)
		duplicate_flag += double_pivot_quick_sort(&array[r_pivot + 1],
				n - r_pivot - 1);
	return (duplicate_flag);
}

/*
* Potentially improving the double pivot quick sorting process, if there are
* many elements to sort, this function first finds the median of three ints,
* given as parameters. Picking the second pivot as the integer which has the
* greater gap between itself and the median can further improve our sorting's
* efficiency; and so, with the help of pick_furthest_pivot(), this function
* finds that pivot as well. At the end of execution, after swapping the
* parameters around, the chosen pivots are stored in variables *a and *c,
* in ascending order - while the leftover value is held by *b - which allows
* the caller to begin the quick sort process.
*/
static void	median_of_three(int *a, int *b, int *c)
{
	if (*a < *b)
	{
		if (*b < *c)
			ft_swap(b, a);
		else
			if (*c > *a)
				ft_swap(c, a);
	}
	else
	{
		if (*b > *c)
			ft_swap(b, a);
		else
			if (*c < *a)
				ft_swap(c, a);
	}
	pick_furthest_pivot(*a, b, c);
	if (*a > *c)
		ft_swap(a, c);
}

/*
* As mentioned in median_of_three()'s comments above, this function compares
* the median (passed as a parameter) with two other integers in order to find
* which of those has the greatest distance between itself and the median.
* That number is subsequently ensured to be placed in *c - while protecting
* the other integer's value within *b. The median remains untouched.
*/
static void	pick_furthest_pivot(int median, int *b, int *c)
{
	int64_t	diff_median_b;
	int64_t	diff_median_c;

	diff_median_b = median - *b;
	if (diff_median_b < 0)
		diff_median_b *= -1;
	diff_median_c = median - *c;
	if (diff_median_c < 0)
		diff_median_c *= -1;
	if (diff_median_b > diff_median_c)
		ft_swap(b, c);
}

/*
* Using the extremities of the array, which serve as pivots, an index i
* scans through the array and compares all other integers to those pivots.
* If a value is found to be equal to one of the pivots, this function returns
* 1 and stops there, since push_swap does not accept duplicates.
* If a value is less than the left pivot, it is placed at the left pivot's
* slot, while all the slots between that location and the index i (including i)
* move one step further. If a value is greater than the right pivot's value,
* it is similarly placed at the right pivot's location, while all the values
* between that location and i move one step 'backwards'. If a value is neither
* less than the left pivot nor greater than the right pivot, no value swaps
* positions, and i advances, until it reaches the right pivot.
* At that point, the array has been divided into three partitions:
* 1. All values smaller than the left pivot
* 2. All values between the left and the right pivots
* 3. All values greater than the right pivot
*/
static uint8_t	sort_and_partition(int *array, size_t *l_pvt, size_t *r_pvt)
{
	size_t	i;

	i = 1;
	if (array[*l_pvt] == array[*r_pvt])
		return (1);
	while (i < *r_pvt)
	{
		if (array[i] == array[*l_pvt] || array[i] == array[*r_pvt])
			return (1);
		if (array[i] < array[*l_pvt])
		{
			swap_and_move(array, i, *l_pvt);
			(*l_pvt)++;
			i++;
		}
		else if (array[i] > array[*r_pvt])
		{
			swap_and_move(array, i, *r_pvt);
			(*r_pvt)--;
		}
		else
			i++;
	}
	return (0);
}

static void	swap_and_move(int *array, size_t i, size_t pvt)
{
	int	temp;

	if (pvt + 1 == i || i + 1 == pvt)
	{
		ft_swap(&array[pvt], &array[i]);
		return ;
	}
	temp = array[i];
	if (i > pvt)
		ft_memmove(&array[pvt + 1], &array[pvt], sizeof(int) * (i - pvt));
	else
		ft_memmove(&array[i], &array[i + 1], sizeof(int) * (pvt - i));
	array[pvt] = temp;
}
