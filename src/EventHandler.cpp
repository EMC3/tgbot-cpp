/*
 * Copyright (c) 2015 Oleg Morozenkov
 * Copyright (c) 2017 Maks Mazurov (fox.cpp)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "tgbot/EventHandler.h"
#include <algorithm>

namespace TgBot {

void EventHandler::handleUpdate(const Update::Ptr update) const {
    if (update->inlineQuery != nullptr) {
        _broadcaster->broadcastInlineQuery(update->inlineQuery);
    }
    if (update->chosenInlineResult != nullptr) {
        _broadcaster->broadcastChosenInlineResult(update->chosenInlineResult);
    }
    if (update->callbackQuery != nullptr) {
        _broadcaster->broadcastCallbackQuery(update->callbackQuery);
    }
    if (update->message != nullptr) {
        handleMessage(update->message);
    }
}

inline void EventHandler::handleMessage(const Message::Ptr message) const {
    _broadcaster->broadcastAnyMessage(message);

    if (StringTools::startsWith(message->text, "/")) {
        uint64_t splitPosition;
        uint64_t spacePosition = message->text.find(' ');
        uint64_t atSymbolPosition = message->text.find('@');
        if (spacePosition == message->text.npos) {
            if (atSymbolPosition == message->text.npos) {
                splitPosition = message->text.size();
            } else {
                splitPosition = atSymbolPosition;
            }
        } else if (atSymbolPosition == message->text.npos) {
            splitPosition = spacePosition;
        } else {
            splitPosition = std::min(spacePosition, atSymbolPosition);
        }
        std::string command = message->text.substr(1, splitPosition - 1);
        if (!_broadcaster->broadcastCommand(command, message)) {
            _broadcaster->broadcastUnknownCommand(message);
        }
    } else {
        _broadcaster->broadcastNonCommandMessage(message);
    }
}

}
