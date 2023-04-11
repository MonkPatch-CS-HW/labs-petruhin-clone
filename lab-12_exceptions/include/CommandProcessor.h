#include <iostream>
#include <functional>
#include <vector>
#include <string>

typedef void (*command_handler_t)(std::istream &in, std::ostream &out);

struct HandlerEntry
{
  std::string name;
  command_handler_t handler;
};

typedef void (*exception_handler_t)(const HandlerEntry &entry, std::exception &ex);

class CommandProcessor
{
public:
  CommandProcessor();

  void add_handler(const std::string &name, command_handler_t handler);
  void set_fallback_handler(command_handler_t handler);
  void set_exception_handler(exception_handler_t handler);

  void remove_handler(command_handler_t handler);
  void remove_handler(const std::string &name);

  void remove_all_handlers();

  bool process_command(const std::string &name, std::istream &in, std::ostream &out) const;

private:
  std::vector<HandlerEntry> _handlers;
  command_handler_t _fallback_handler;
  exception_handler_t _exception_handler;
};