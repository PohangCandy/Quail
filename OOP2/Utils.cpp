#include "Utils.h"


bool isOverlap(int src_start, int src_end, int target_start, int target_end)
{
	return src_end > target_start && target_end > src_start;
}