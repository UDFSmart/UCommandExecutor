
/*
 *    Copyright 2026 UDFOwner
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *
 *    More details: https://udfsoft.com/
 */

#include "UCommandExecutor.h"

UCommandExecutor::UCommandExecutor(const UCommand* commands, size_t count)
  : _commands(commands), _commandsCount(count) {}

void UCommandExecutor::execute(const char* cmd, const char* param, CommandResultCallback callback) {
  if (!cmd || strlen(cmd) == 0) {
    if (callback) callback(cmd, param, "Empty command");
    return;
  }

  for (size_t i = 0; i < _commandsCount; ++i) {
    if (strcasecmp(_commands[i].name, cmd) == 0) {  // if _commands[i].name == cmd
      _commands[i].function(param, callback);       // execute _commands[i]

      return;
    }
  }

  if (callback) callback(cmd, param, "Unknown command");
}