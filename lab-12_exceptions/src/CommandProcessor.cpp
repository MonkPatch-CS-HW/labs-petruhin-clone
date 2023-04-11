#include <algorithm>

#include "CommandProcessor.h"

CommandProcessor::CommandProcessor() {}

void CommandProcessor::add_handler(const std::string &name, command_handler_t handler)
{
  _handlers.push_back(HandlerEntry{.name = name, .handler = handler});
}

bool CommandProcessor::process_command(const std::string &name, std::istream &in, std::ostream &out) const
{
  bool processed = false;

  for (auto &entry : _handlers)
  {
    if (entry.name != name)
      continue;

    try
    {
      entry.handler(in, out);
    }
    catch (std::exception &ex)
    {
      if (_exception_handler != nullptr)
        _exception_handler(entry, ex);
      else
        throw;
    }

    processed = true;
  }

  if (!processed && _fallback_handler != nullptr)
    _fallback_handler(in, out);

  return processed;
}

void CommandProcessor::set_exception_handler(exception_handler_t handler)
{
  _exception_handler = handler;
}

void CommandProcessor::set_fallback_handler(command_handler_t handler)
{
  _fallback_handler = handler;
}

void CommandProcessor::remove_all_handlers()
{
  _handlers.clear();
}

void CommandProcessor::remove_handler(const std::string &name)
{
  std::remove_if(
      _handlers.begin(),
      _handlers.end(),
      [&name](const HandlerEntry &entry)
      {
        return entry.name == name;
      });
}

void CommandProcessor::remove_handler(const command_handler_t handler)
{
  std::remove_if(
      _handlers.begin(),
      _handlers.end(),
      [&handler](const HandlerEntry &entry)
      {
        return entry.handler == handler;
      });
}