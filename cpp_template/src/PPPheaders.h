// PPPheaders.h

#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <random>
#include <set>
#include <span>
#include <sstream>
#include <stdexcept>
#include <stdint.h>
#include <string>
#include <unordered_map>
#include <vector>

#define PPP_EXPORT
#include "PPP_support.h"

using namespace std;
using namespace PPP;

// disgusting macro hack to get a range checking:
#define vector Checked_vector
#define string Checked_string
#define span   Checked_span
