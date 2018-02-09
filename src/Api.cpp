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

#include "tgbot/Api.h"

#include "tgbot/TgTypeParser.h"
#include "tgbot/TgException.h"
#include "tgbot/net/HttpClient.h"

using namespace boost::property_tree;

namespace TgBot {

Api::Api(const std::string& token) : _token(token) {
}

User::Ptr Api::getMe() const {
	return TgTypeParser::parseJsonAndGetUser(sendRequest("getMe"));
}

Message::Ptr Api::sendMessage(int64_t chatId, const std::string& text, bool disableWebPagePreview, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup, const std::string& parseMode, bool disableNotification) const {
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("text", text));
	if (disableWebPagePreview) {
		args.push_back(HttpReqArg("disable_web_page_preview", disableWebPagePreview));
	}
	if (disableNotification){
		args.push_back(HttpReqArg("disable_notification", disableNotification));
	}
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::parseGenericReply(replyMarkup)));
	}
	if (!parseMode.empty()) {
		args.push_back(HttpReqArg("parse_mode", parseMode));
	}
	return TgTypeParser::parseJsonAndGetMessage(sendRequest("sendMessage", args));
}

Message::Ptr Api::forwardMessage(int64_t chatId, int64_t fromChatId, int32_t messageId, bool disableNotification) const {
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("from_chat_id", fromChatId));
	args.push_back(HttpReqArg("message_id", messageId));
	if (disableNotification){
		args.push_back(HttpReqArg("disable_notification", disableNotification));
	}
	return TgTypeParser::parseJsonAndGetMessage(sendRequest("forwardMessage", args));
}

Message::Ptr Api::sendPhoto(int64_t chatId, const InputFile::Ptr photo, const std::string& caption, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup, bool disableNotification) const {
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("photo", photo->data, true, photo->mimeType, photo->fileName));
	if (!caption.empty()) {
		args.push_back(HttpReqArg("caption", caption));
	}
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::parseGenericReply(replyMarkup)));
	}
	if (disableNotification){
		args.push_back(HttpReqArg("disable_notification", disableNotification));
	}
	return TgTypeParser::parseJsonAndGetMessage(sendRequest("sendPhoto", args));
}

Message::Ptr Api::sendPhoto(int64_t chatId, const std::string& photoId, const std::string& caption, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup, bool disableNotification) const {
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("photo", photoId));
	if (!caption.empty()) {
		args.push_back(HttpReqArg("caption", caption));
	}
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::parseGenericReply(replyMarkup)));
	}
	if (disableNotification){
		args.push_back(HttpReqArg("disable_notification", disableNotification));
	}
	return TgTypeParser::parseJsonAndGetMessage(sendRequest("sendPhoto", args));
}

Message::Ptr Api::sendAudio(int64_t chatId, const InputFile::Ptr audio, const std::string &caption, int32_t duration, const std::string& performer, const std::string& title, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup, bool disableNotification) const {
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("audio", audio->data, true, audio->mimeType, audio->fileName));
	if (!caption.empty()) {
		args.push_back(HttpReqArg("caption", caption));
	}
	if (duration) {
		args.push_back(HttpReqArg("duration", duration));
	}
	if (!performer.empty()){
		args.push_back(HttpReqArg("performer", performer));
	}
	if (!title.empty()){
		args.push_back(HttpReqArg("title", title));
	}
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::parseGenericReply(replyMarkup)));
	}
	if (disableNotification){
		args.push_back(HttpReqArg("disable_notification", disableNotification));
	}
	return TgTypeParser::parseJsonAndGetMessage(sendRequest("sendAudio", args));
}

Message::Ptr Api::sendAudio(int64_t chatId, const std::string& audioId, const std::string &caption, int32_t duration, const std::string& performer, const std::string& title, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup, bool disableNotification) const {
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("audio", audioId));
	if (!caption.empty()) {
		args.push_back(HttpReqArg("caption", caption));
	}
	if (duration) {
		args.push_back(HttpReqArg("duration", duration));
	}
	if (!performer.empty()){
		args.push_back(HttpReqArg("performer", performer));
	}
	if (!title.empty()){
		args.push_back(HttpReqArg("title", title));
	}
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::parseGenericReply(replyMarkup)));
	}
	if (disableNotification){
		args.push_back(HttpReqArg("disable_notification", disableNotification));
	}
	return TgTypeParser::parseJsonAndGetMessage(sendRequest("sendAudio", args));
}

Message::Ptr Api::sendDocument(int64_t chatId, const InputFile::Ptr document, const std::string &caption, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup, bool disableNotification) const {
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("document", document->data, true, document->mimeType, document->fileName));
	if (!caption.empty()) {
		args.push_back(HttpReqArg("caption", caption));
	}
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::parseGenericReply(replyMarkup)));
	}
	if (disableNotification){
		args.push_back(HttpReqArg("disable_notification", disableNotification));
	}
	return TgTypeParser::parseJsonAndGetMessage(sendRequest("sendDocument", args));
}

Message::Ptr Api::sendDocument(int64_t chatId, const std::string& document, const std::string &caption, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup, bool disableNotification) const {
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("document", document));
	if (!caption.empty()) {
		args.push_back(HttpReqArg("caption", caption));
	}
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::parseGenericReply(replyMarkup)));
	}
	if (disableNotification){
		args.push_back(HttpReqArg("disable_notification", disableNotification));
	}
	return TgTypeParser::parseJsonAndGetMessage(sendRequest("sendDocument", args));
}

Message::Ptr Api::sendSticker(int64_t chatId, const InputFile::Ptr sticker, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup, bool disableNotification) const {
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("sticker", sticker->data, true, sticker->mimeType, sticker->fileName));
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::parseGenericReply(replyMarkup)));
	}
	if (disableNotification){
		args.push_back(HttpReqArg("disable_notification", disableNotification));
	}
	return TgTypeParser::parseJsonAndGetMessage(sendRequest("sendSticker", args));
}

Message::Ptr Api::sendSticker(int64_t chatId, const std::string& stickerId, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup, bool disableNotification) const {
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("sticker", stickerId));
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::parseGenericReply(replyMarkup)));
	}
	if (disableNotification){
		args.push_back(HttpReqArg("disable_notification", disableNotification));
	}
	return TgTypeParser::parseJsonAndGetMessage(sendRequest("sendSticker", args));
}

Message::Ptr Api::sendVideo(int64_t chatId, const InputFile::Ptr video, int32_t duration, int32_t width, int32_t height, const std::string &caption, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup, bool disableNotification) const {
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("video", video->data, true, video->mimeType, video->fileName));
	if (duration) {
		args.push_back(HttpReqArg("duration", duration));
	}
	if (width) {
		args.push_back(HttpReqArg("width", width));
	}
	if (height) {
		args.push_back(HttpReqArg("height", height));
	}
	if (!caption.empty()) {
		args.push_back(HttpReqArg("caption", caption));
	}
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::parseGenericReply(replyMarkup)));
	}
	if (disableNotification){
		args.push_back(HttpReqArg("disable_notification", disableNotification));
	}
	return TgTypeParser::parseJsonAndGetMessage(sendRequest("sendVideo", args));
}

Message::Ptr Api::sendVideo(int64_t chatId, const std::string& videoId, int32_t duration, int32_t width, int32_t height, const std::string &caption, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup, bool disableNotification) const {
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("video", videoId));
	if (duration) {
		args.push_back(HttpReqArg("duration", duration));
	}
	if (width) {
		args.push_back(HttpReqArg("width", width));
	}
	if (height) {
		args.push_back(HttpReqArg("height", height));
	}
	if (!caption.empty()) {
		args.push_back(HttpReqArg("caption", caption));
	}
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::parseGenericReply(replyMarkup)));
	}
	if (disableNotification){
		args.push_back(HttpReqArg("disable_notification", disableNotification));
	}
	return TgTypeParser::parseJsonAndGetMessage(sendRequest("sendVideo", args));
}

Message::Ptr Api::sendVideoNote(int64_t chatId, const InputFile::Ptr videoNote, int64_t replyToMessageId, bool disableNotification, int32_t duration, int32_t length, const GenericReply::Ptr replyMarkup) {
    std::vector<HttpReqArg> args;
    args.push_back(HttpReqArg("chat_id", chatId));
    args.push_back(HttpReqArg("video_note", videoNote));
    if (replyToMessageId) {
        args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
    }
    if (disableNotification) {
        args.push_back(HttpReqArg("disable_notification", disableNotification));
    }
    if (duration) {
        args.push_back(HttpReqArg("duration", duration));
    }
    if (length) {
        args.push_back(HttpReqArg("length", length));
    }
    if (replyMarkup) {
        args.push_back(HttpReqArg("reply_markup", TgTypeParser::parseGenericReply(replyMarkup)));
    }
    return TgTypeParser::parseJsonAndGetMessage(sendRequest("sendVoiceNote", args));
}

Message::Ptr Api::sendVideoNote(int64_t chatId, const std::string &videoNote, int64_t replyToMessageId, bool disableNotification, int32_t duration, int32_t length, const GenericReply::Ptr replyMarkup) {
    std::vector<HttpReqArg> args;
    args.push_back(HttpReqArg("chat_id", chatId));
    args.push_back(HttpReqArg("video_note", videoNote));
    if (replyToMessageId) {
        args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
    }
    if (disableNotification) {
        args.push_back(HttpReqArg("disable_notification", disableNotification));
    }
    if (duration) {
        args.push_back(HttpReqArg("duration", duration));
    }
    if (length) {
        args.push_back(HttpReqArg("length", length));
    }
    if (replyMarkup) {
        args.push_back(HttpReqArg("reply_markup", TgTypeParser::parseGenericReply(replyMarkup)));
    }
    return TgTypeParser::parseJsonAndGetMessage(sendRequest("sendVoiceNote", args));
}

Message::Ptr Api::sendVoice(int64_t chatId, const InputFile::Ptr voice, const std::string &caption, int duration, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup, bool disableNotification) const {
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("voice", voice->data, true, voice->mimeType, voice->fileName));
	if (!caption.empty()) {
		args.push_back(HttpReqArg("caption", caption));
	}
	if (duration){
		args.push_back(HttpReqArg("duration", duration));
	}
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::parseGenericReply(replyMarkup)));
	}
	if (disableNotification){
		args.push_back(HttpReqArg("disable_notification", disableNotification));
	}
	return TgTypeParser::parseJsonAndGetMessage(sendRequest("sendVoice", args));
}

Message::Ptr Api::sendVoice(int64_t chatId, const std::string& voiceId, const std::string &caption, int duration, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup, bool disableNotification) const {
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("voice", voiceId));
	if (!caption.empty()) {
		args.push_back(HttpReqArg("caption", caption));
	}
	if (duration){
		args.push_back(HttpReqArg("duration", duration));
	}
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::parseGenericReply(replyMarkup)));
	}
	if (disableNotification){
		args.push_back(HttpReqArg("disable_notification", disableNotification));
	}
	return TgTypeParser::parseJsonAndGetMessage(sendRequest("sendVoice", args));
}

Message::Ptr Api::sendLocation(int64_t chatId, float latitude, float longitude, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup, bool disableNotification) const {
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("latitude", latitude));
	args.push_back(HttpReqArg("longitude", longitude));
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::parseGenericReply(replyMarkup)));
	}
	if (disableNotification){
		args.push_back(HttpReqArg("disable_notification", disableNotification));
	}
	return TgTypeParser::parseJsonAndGetMessage(sendRequest("sendLocation", args));
}

Message::Ptr Api::sendVenue(int64_t chatId, float latitude, float longitude, std::string title, std::string address, std::string foursquareId, bool disableNotification, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup) const {
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("latitude", latitude));
	args.push_back(HttpReqArg("longitude", longitude));
	args.push_back(HttpReqArg("title", title));
	args.push_back(HttpReqArg("address", address));
	if (!foursquareId.empty()) {
		args.push_back(HttpReqArg("foursquare_id", foursquareId));
	}
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::parseGenericReply(replyMarkup)));
	}
	if (disableNotification){
		args.push_back(HttpReqArg("disable_notification", disableNotification));
	}
	return TgTypeParser::parseJsonAndGetMessage(sendRequest("sendVenue", args));
}

Message::Ptr Api::sendContact(int64_t chatId, std::string phoneNumber, std::string firstName, std::string lastName, bool disableNotification, int32_t replyToMessageId, const GenericReply::Ptr replyMarkup) const {
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("phone_number", phoneNumber));
	args.push_back(HttpReqArg("first_name", firstName));
	args.push_back(HttpReqArg("last_name", lastName));
	if (replyToMessageId) {
		args.push_back(HttpReqArg("reply_to_message_id", replyToMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::parseGenericReply(replyMarkup)));
	}
	if (disableNotification){
		args.push_back(HttpReqArg("disable_notification", disableNotification));
	}
	return TgTypeParser::parseJsonAndGetMessage(sendRequest("sendContact", args));
}

void Api::sendChatAction(int64_t chatId, const std::string& action) const {
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("action", action));
	sendRequest("sendChatAction", args);
}

UserProfilePhotos::Ptr Api::getUserProfilePhotos(int32_t userId, int32_t offset, int32_t limit) const {
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("user_id", userId));
	if (offset) {
		args.push_back(HttpReqArg("offset", offset));
	}
	limit = std::max(1, std::min(100, limit));
	args.push_back(HttpReqArg("limit", limit));
	return TgTypeParser::parseJsonAndGetUserProfilePhotos(sendRequest("getUserProfilePhotos", args));
}

File::Ptr Api::getFile(const std::string &fileId) const
{
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("file_id", fileId));
	return TgTypeParser::parseJsonAndGetFile(sendRequest("getFile", args));
}

bool Api::leaveChat(int64_t chatId) const
{
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	return sendRequest("leaveChat", args).get<bool>("", false);
}

Chat::Ptr Api::getChat(int64_t chatId) const
{
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	return TgTypeParser::parseJsonAndGetChat(sendRequest("getChat", args));
}

std::vector<ChatMember::Ptr> Api::getChatAdministrators(int64_t chatId) const
{
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	return TgTypeParser::parseJsonAndGetArray<ChatMember>(&TgTypeParser::parseJsonAndGetChatMember, sendRequest("getChatAdministrators", args));
}

int32_t Api::getChatMembersCount(int64_t chatId) const
{
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	return sendRequest("getChatMembersCount", args).get<int32_t>("", 0);
}

bool Api::answerCallbackQuery(const std::string & callbackQueryId, const std::string & text, bool showAlert, const std::string &url, int32_t cacheTime) const
{
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("callback_query_id", callbackQueryId));
	if (!text.empty()) {
		args.push_back(HttpReqArg("text", text));
	}
	if (showAlert) {
		args.push_back(HttpReqArg("show_alert", showAlert));
	}
	if (!url.empty()) {
		args.push_back(HttpReqArg("url", url));
	}
	if (cacheTime) {
		args.push_back(HttpReqArg("cache_time", cacheTime));
	}
	return sendRequest("answerCallbackQuery", args).get<bool>("", false);
}

Message::Ptr Api::editMessageText(const std::string& text, int64_t chatId, int32_t messageId, const std::string& inlineMessageId,
	const std::string& parseMode, bool disableWebPagePreview, const GenericReply::Ptr replyMarkup) const {

	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("text", text));
	if (chatId) {
		args.push_back(HttpReqArg("chat_id", chatId));
	}
	if (messageId) {
		args.push_back(HttpReqArg("message_id", messageId));
	}
	if (!inlineMessageId.empty()) {
		args.push_back(HttpReqArg("inline_message_id", inlineMessageId));
	}
	if (!parseMode.empty()) {
		args.push_back(HttpReqArg("parse_mode", parseMode));
	}
	if (disableWebPagePreview) {
		args.push_back(HttpReqArg("disable_web_page_preview", disableWebPagePreview));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::parseGenericReply(replyMarkup)));
	}
	ptree p = sendRequest("editMessageText", args);
	if (p.get_child_optional("message_id")) {
		return TgTypeParser::parseJsonAndGetMessage(p);
	} else {
		return nullptr;
	}	
}

Message::Ptr Api::editMessageCaption(int64_t chatId, int32_t messageId, const std::string& caption,
									 const std::string& inlineMessageId, const GenericReply::Ptr replyMarkup) const {

	std::vector<HttpReqArg> args;
	if (chatId) {
		args.push_back(HttpReqArg("chat_id", chatId));
	}
	if (messageId) {
		args.push_back(HttpReqArg("message_id", messageId));
	}
	if (!caption.empty()) {
		args.push_back(HttpReqArg("caption", caption));
	}
	if (!inlineMessageId.empty()) {
		args.push_back(HttpReqArg("inline_message_id", inlineMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::parseGenericReply(replyMarkup)));
	}
	ptree p = sendRequest("editMessageCaption", args);
	if (p.get_child_optional("message_id")) {
		return TgTypeParser::parseJsonAndGetMessage(p);
	} else {
		return nullptr;
	}

}

Message::Ptr Api::editMessageReplyMarkup(int64_t chatId, int32_t messageId, const std::string& inlineMessageId,
										 const GenericReply::Ptr replyMarkup) const {

	std::vector<HttpReqArg> args;
	if (chatId) {
		args.push_back(HttpReqArg("chat_id", chatId));
	}
	if (messageId) {
		args.push_back(HttpReqArg("message_id", messageId));
	}
	if (!inlineMessageId.empty()) {
		args.push_back(HttpReqArg("inline_message_id", inlineMessageId));
	}
	if (replyMarkup) {
		args.push_back(HttpReqArg("reply_markup", TgTypeParser::parseGenericReply(replyMarkup)));
	}
	ptree p = sendRequest("editMessageReplyMarkup", args);
	if (p.get_child_optional("message_id")) {
		return TgTypeParser::parseJsonAndGetMessage(p);
	} else {
		return nullptr;
	}
}

ChatMember::Ptr Api::getChatMember(int64_t chatId, int32_t userId) const
{
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("user_id", userId));
	return TgTypeParser::parseJsonAndGetChatMember(sendRequest("getChatMember", args));
}

std::vector<Update::Ptr> Api::getUpdates(int32_t offset, int32_t limit, int32_t timeout, const StringArrayPtr &allowedUpdates) const {
	std::vector<HttpReqArg> args;
	if (offset) {
		args.push_back(HttpReqArg("offset", offset));
	}
	limit = std::max(1, std::min(100, limit));
	args.push_back(HttpReqArg("limit", limit));
	if (timeout) {
		args.push_back(HttpReqArg("timeout", timeout));
	}
	if (allowedUpdates!=nullptr) {
		std::string allowedUpdatesJson = TgTypeParser::parseArray<std::string>(
			[](const std::string &s)->std::string {
			return s;
		}, *allowedUpdates);
		args.push_back(HttpReqArg("allowed_updates", allowedUpdatesJson));
	}
	return TgTypeParser::parseJsonAndGetArray<Update>(&TgTypeParser::parseJsonAndGetUpdate, sendRequest("getUpdates", args));
}

void Api::setWebhook(const std::string& url, const InputFile::Ptr certificate, int32_t maxConnection, const StringArrayPtr &allowedUpdates) const {
	std::vector<HttpReqArg> args;
	if (!url.empty())
		args.push_back(HttpReqArg("url", url));
	if (certificate != nullptr)
		args.push_back(HttpReqArg("certificate", certificate->data, true, certificate->mimeType, certificate->fileName));
	if (maxConnection!=40)
		args.push_back(HttpReqArg("max_connections", maxConnection));
	
	if (allowedUpdates!=nullptr)
	{
		std::string allowedUpdatesJson = TgTypeParser::parseArray<std::string>(
			[](const std::string &s)->std::string {
				return s;
			}, *allowedUpdates);
		args.push_back(HttpReqArg("allowed_updates", allowedUpdatesJson));
	}

	sendRequest("setWebhook", args);
}

bool Api::deleteWebhook() const
{
	ptree p = sendRequest("deleteWebhook");
	return p.get<bool>("", false);
}

WebhookInfo::Ptr Api::getWebhookInfo() const
{
	ptree p = sendRequest("getWebhookInfo");

	if (!p.get_child_optional("url"))
		return nullptr;

	if (p.get<std::string>("url","")!=std::string(""))
	{
		return TgTypeParser::parseJsonAndGetWebhookInfo(p);
	} 
	else 
	{
		return nullptr;
	}
}

bool Api::answerInlineQuery(const std::string& inlineQueryId, const std::vector<InlineQueryResult::Ptr>& results,
	int32_t cacheTime, bool isPersonal, const std::string& nextOffset, const std::string& switchPmText, const std::string& switchPmParameter) const {
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("inline_query_id", inlineQueryId));
	std::string resultsJson = TgTypeParser::parseArray<InlineQueryResult>(&TgTypeParser::parseInlineQueryResult, results);
	args.push_back(HttpReqArg("results", resultsJson));
	if (cacheTime) {
		args.push_back(HttpReqArg("cache_time", cacheTime));
	}
	if (isPersonal) {
		args.push_back(HttpReqArg("is_personal", isPersonal));
	}
	if (!nextOffset.empty()) {
		args.push_back(HttpReqArg("next_offset", nextOffset));
	}
	if (!switchPmText.empty()) {
		args.push_back(HttpReqArg("switch_pm_text", switchPmText));
	}
	if (!switchPmParameter.empty()) {
		args.push_back(HttpReqArg("switch_pm_parameter", switchPmParameter));
	}
	return sendRequest("answerInlineQuery", args).get<bool>("", false);
}

bool Api::kickChatMember(int64_t chatId, int32_t userId) const {
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("user_id", userId));
	return sendRequest("kickChatMember", args).get<bool>("", false);
}

bool Api::unbanChatMember(int64_t chatId, int32_t userId) const {
	std::vector<HttpReqArg> args;
	args.push_back(HttpReqArg("chat_id", chatId));
	args.push_back(HttpReqArg("user_id", userId));
	return sendRequest("unbanChatMember", args).get<bool>("", false);
}

void Api::deleteMessage(int64_t chatId, int32_t messageId) const {
	sendRequest("deleteMessage", { HttpReqArg("chat_id", chatId), HttpReqArg("message_id", messageId) });
}

ptree Api::sendRequest(const std::string& method, const std::vector<HttpReqArg>& args) const {
	std::string url = "https://api.telegram.org/bot";
	url += _token;
	url += "/";
	url += method;

	std::string serverResponse = HttpClient::getInstance().makeRequest(url, args);
	if (!serverResponse.compare(0, 6, "<html>")) {
		throw TgException("tgbot-cpp library have got html page instead of json response. Maybe you entered wrong bot token.");
	}

	ptree result = TgTypeParser::parseJson(serverResponse);
	try {
		if (result.get<bool>("ok", false)) {
			return result.get_child("result");
		} else {
			throw TgException(result.get("description", ""));
		}
	} catch (boost::property_tree::ptree_error& e) {
		throw TgException("tgbot-cpp library can't parse json response. " + std::string(e.what()));
	}
}

std::string Api::downloadFile(const std::string& filePath, const std::vector<HttpReqArg>& args) const {
	std::string url = "https://api.telegram.org/file/bot";
	url += _token;
	url += "/";
	url += filePath;

	std::string serverResponse = HttpClient::makeRequest(url, args);

	return serverResponse;
}

}
