/*
 * @name BookFiler™ Module for HTTP
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief HTTP Module
 */

#ifndef BOOKFILER_MODULE_HTTP_H
#define BOOKFILER_MODULE_HTTP_H

// c++17
#include <functional>
#include <memory>
#include <string_view>

/*
 * bookfiler = BookFiler™
 */
namespace bookfiler {

class Http {
public:
  void get(std::string);
  void onSocket(std::function<void(Http)>);
  void onResponse(std::function<void(Http, std::string_view)>);
  void onClose(std::function<void(Http)>);
};

} // namespace bookfiler

#endif // end BOOKFILER_MODULE_HTTP_H
