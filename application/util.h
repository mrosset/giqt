#ifndef _QT_UTIL_H_
#define _QT_UTIL_H_

#include <functional>

void DispatchOnMainThread (std::function<void()> callback);

#endif /* _QT_UTIL_H_ */
