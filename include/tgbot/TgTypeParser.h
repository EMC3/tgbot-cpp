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

#ifndef TGBOT_CPP_TGTYPEPARSER_H
#define TGBOT_CPP_TGTYPEPARSER_H

#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "tgbot/types.h"

namespace TgBot {

namespace TgTypeParser {
	template<typename T>
	using JsonToTgTypeFunc = std::shared_ptr<T> (*)(const boost::property_tree::ptree&);

	template<typename T>
	using TgTypeToJsonFunc = std::string (*)(const std::shared_ptr<T>&);

	Chat::Ptr parseJsonAndGetChat(const boost::property_tree::ptree& data);
	std::string parseChat(const Chat::Ptr& object);
	User::Ptr parseJsonAndGetUser(const boost::property_tree::ptree& data);
	std::string parseUser(const User::Ptr& object);
	MessageEntity::Ptr parseJsonAndGetEntity(const boost::property_tree::ptree& data);
	Message::Ptr parseJsonAndGetMessage(const boost::property_tree::ptree& data);
	std::string parseMessage(const Message::Ptr& object);
	PhotoSize::Ptr parseJsonAndGetPhotoSize(const boost::property_tree::ptree& data);
	std::string parsePhotoSize(const PhotoSize::Ptr& object);
	Audio::Ptr parseJsonAndGetAudio(const boost::property_tree::ptree& data);
	std::string parseAudio(const Audio::Ptr& object);
	Document::Ptr parseJsonAndGetDocument(const boost::property_tree::ptree& data);
	std::string parseDocument(const Document::Ptr& object);
	Sticker::Ptr parseJsonAndGetSticker(const boost::property_tree::ptree& data);
	std::string parseSticker(const Sticker::Ptr& object);
	Video::Ptr parseJsonAndGetVideo(const boost::property_tree::ptree& data);
	std::string parseVideo(const Video::Ptr& object);
	VideoNote::Ptr parseJsonAndGetVideoNote(const boost::property_tree::ptree& data);
	std::string parseVideoNote(const VideoNote::Ptr& object);
	Contact::Ptr parseJsonAndGetContact(const boost::property_tree::ptree& data);
	std::string parseContact(const Contact::Ptr& object);
	Location::Ptr parseJsonAndGetLocation(const boost::property_tree::ptree& data);
	std::string parseLocation(const Location::Ptr& object);
	Update::Ptr parseJsonAndGetUpdate(const boost::property_tree::ptree& data);
	std::string parseUpdate(const Update::Ptr& object);
	UserProfilePhotos::Ptr parseJsonAndGetUserProfilePhotos(const boost::property_tree::ptree& data);
	std::string parseUserProfilePhotos(const UserProfilePhotos::Ptr& object);

	File::Ptr parseJsonAndGetFile(const boost::property_tree::ptree& data);
	std::string parseFile(const File::Ptr& object);

	ReplyKeyboardMarkup::Ptr parseJsonAndGetReplyKeyboardMarkup(const boost::property_tree::ptree& data);
	std::string parseReplyKeyboardMarkup(const ReplyKeyboardMarkup::Ptr& object);

	KeyboardButton::Ptr parseJsonAndGetKeyboardButton(const boost::property_tree::ptree& data);
	std::string parseKeyboardButton(const KeyboardButton::Ptr& object);

	ReplyKeyboardRemove::Ptr parseJsonAndGetReplyKeyboardRemove(const boost::property_tree::ptree& data);
	std::string parseReplyKeyboardRemove(const ReplyKeyboardRemove::Ptr& object);

	ForceReply::Ptr parseJsonAndGetForceReply(const boost::property_tree::ptree& data);
	std::string parseForceReply(const ForceReply::Ptr& object);

	ChatMember::Ptr parseJsonAndGetChatMember(const boost::property_tree::ptree& data);
	std::string parseChatMember(const ChatMember::Ptr& object);

	ResponseParameters::Ptr parseJsonAndGetResponseParameters(const boost::property_tree::ptree& data);
	std::string parseResponseParameters(const ResponseParameters::Ptr& object);

	GenericReply::Ptr parseJsonAndGetGenericReply(const boost::property_tree::ptree& data);
	std::string parseGenericReply(const GenericReply::Ptr& object);
	
	InlineQuery::Ptr parseJsonAndGetInlineQuery(const boost::property_tree::ptree& data);
	std::string parseInlineQuery(const InlineQuery::Ptr& object);
	
	InlineQueryResult::Ptr parseJsonAndGetInlineQueryResult(const boost::property_tree::ptree& data);
	std::string parseInlineQueryResult(const InlineQueryResult::Ptr& object);
	
	InlineQueryResultCachedAudio::Ptr parseJsonAndGetInlineQueryResultCachedAudio(const boost::property_tree::ptree& data);
	std::string parseInlineQueryResultCachedAudio(const InlineQueryResultCachedAudio::Ptr& object);

	InlineQueryResultCachedDocument::Ptr parseJsonAndGetInlineQueryResultCachedDocument(const boost::property_tree::ptree& data);
	std::string parseInlineQueryResultCachedDocument(const InlineQueryResultCachedDocument::Ptr& object);

	InlineQueryResultCachedGif::Ptr parseJsonAndGetInlineQueryResultCachedGif(const boost::property_tree::ptree& data);
	std::string parseInlineQueryResultCachedGif(const InlineQueryResultCachedGif::Ptr& object);

	InlineQueryResultCachedMpeg4Gif::Ptr parseJsonAndGetInlineQueryResultCachedMpeg4Gif(const boost::property_tree::ptree& data);
	std::string parseInlineQueryResultCachedMpeg4Gif(const InlineQueryResultCachedMpeg4Gif::Ptr& object);

	InlineQueryResultCachedPhoto::Ptr parseJsonAndGetInlineQueryResultCachedPhoto(const boost::property_tree::ptree& data);
	std::string parseInlineQueryResultCachedPhoto(const InlineQueryResultCachedPhoto::Ptr& object);

	InlineQueryResultCachedSticker::Ptr parseJsonAndGetInlineQueryResultCachedSticker(const boost::property_tree::ptree& data);
	std::string parseInlineQueryResultCachedSticker(const InlineQueryResultCachedSticker::Ptr& object);

	InlineQueryResultCachedVideo::Ptr parseJsonAndGetInlineQueryResultCachedVideo(const boost::property_tree::ptree& data);
	std::string parseInlineQueryResultCachedVideo(const InlineQueryResultCachedVideo::Ptr& object);

	InlineQueryResultCachedVoice::Ptr parseJsonAndGetInlineQueryResultCachedVoice(const boost::property_tree::ptree& data);
	std::string parseInlineQueryResultCachedVoice(const InlineQueryResultCachedVoice::Ptr& object);

	InlineQueryResultArticle::Ptr parseJsonAndGetInlineQueryResultArticle(const boost::property_tree::ptree& data);
	std::string parseInlineQueryResultArticle(const InlineQueryResultArticle::Ptr& object);

	InlineQueryResultAudio::Ptr parseJsonAndGetInlineQueryResultAudio(const boost::property_tree::ptree& data);
	std::string parseInlineQueryResultAudio(const InlineQueryResultAudio::Ptr& object);

	InlineQueryResultContact::Ptr parseJsonAndGetInlineQueryResultContact(const boost::property_tree::ptree& data);
	std::string parseInlineQueryResultContact(const InlineQueryResultContact::Ptr& object);

	InlineQueryResultGame::Ptr parseJsonAndGetInlineQueryResultGame(const boost::property_tree::ptree& data);
	std::string parseInlineQueryResultGame(const InlineQueryResultGame::Ptr& object);

	InlineQueryResultDocument::Ptr parseJsonAndGetInlineQueryResultDocument(const boost::property_tree::ptree& data);
	std::string parseInlineQueryResultDocument(const InlineQueryResultDocument::Ptr& object);

	InlineQueryResultLocation::Ptr parseJsonAndGetInlineQueryResultLocation(const boost::property_tree::ptree& data);
	std::string parseInlineQueryResultLocation(const InlineQueryResultLocation::Ptr& object);

	InlineQueryResultVenue::Ptr parseJsonAndGetInlineQueryResultVenue(const boost::property_tree::ptree& data);
	std::string parseInlineQueryResultVenue(const InlineQueryResultVenue::Ptr& object);

	InlineQueryResultVoice::Ptr parseJsonAndGetInlineQueryResultVoice(const boost::property_tree::ptree& data);
	std::string parseInlineQueryResultVoice(const InlineQueryResultVoice::Ptr& object);

	InlineQueryResultPhoto::Ptr parseJsonAndGetInlineQueryResultPhoto(const boost::property_tree::ptree& data);
	std::string parseInlineQueryResultPhoto(const InlineQueryResultPhoto::Ptr& object);
	InlineQueryResultGif::Ptr parseJsonAndGetInlineQueryResultGif(const boost::property_tree::ptree& data);
	std::string parseInlineQueryResultGif(const InlineQueryResultGif::Ptr& object);
	InlineQueryResultMpeg4Gif::Ptr parseJsonAndGetInlineQueryResultMpeg4Gif(const boost::property_tree::ptree& data);
	std::string parseInlineQueryResultMpeg4Gif(const InlineQueryResultMpeg4Gif::Ptr& object);
	InlineQueryResultVideo::Ptr parseJsonAndGetInlineQueryResultVideo(const boost::property_tree::ptree& data);
	std::string parseInlineQueryResultVideo(const InlineQueryResultVideo::Ptr& object);
	ChosenInlineResult::Ptr parseJsonAndGetChosenInlineResult(const boost::property_tree::ptree& data);
	std::string parseChosenInlineResult(const ChosenInlineResult::Ptr& object);

	CallbackQuery::Ptr parseJsonAndGetCallbackQuery(const boost::property_tree::ptree& data);
	std::string parseCallbackQuery(const CallbackQuery::Ptr& object);
	InlineKeyboardMarkup::Ptr parseJsonAndGetInlineKeyboardMarkup(const boost::property_tree::ptree& data);
	std::string parseInlineKeyboardMarkup(const InlineKeyboardMarkup::Ptr& object);
	InlineKeyboardButton::Ptr parseJsonAndGetInlineKeyboardButton(const boost::property_tree::ptree& data);
	std::string parseInlineKeyboardButton(const InlineKeyboardButton::Ptr& object);

	WebhookInfo::Ptr parseJsonAndGetWebhookInfo(const boost::property_tree::ptree& data);
	std::string parseWebhookInfo(const WebhookInfo::Ptr& object);

	InputMessageContent::Ptr parseJsonAndGetInputMessageContent(const boost::property_tree::ptree& data);
	std::string parseInputMessageContent(const InputMessageContent::Ptr& object);

	InputTextMessageContent::Ptr parseJsonAndGetInputTextMessageContent(const boost::property_tree::ptree& data);
	std::string parseInputTextMessageContent(const InputTextMessageContent::Ptr& object);

	InputLocationMessageContent::Ptr parseJsonAndGetInputLocationMessageContent(const boost::property_tree::ptree& data);
	std::string parseInputLocationMessageContent(const InputLocationMessageContent::Ptr& object);

	InputVenueMessageContent::Ptr parseJsonAndGetInputVenueMessageContent(const boost::property_tree::ptree& data);
	std::string parseInputVenueMessageContent(const InputVenueMessageContent::Ptr& object);

	InputContactMessageContent::Ptr parseJsonAndGetInputContactMessageContent(const boost::property_tree::ptree& data);
	std::string parseInputContactMessageContent(const InputContactMessageContent::Ptr& object);

	Invoice::Ptr parseJsonAndGetInvoice(const boost::property_tree::ptree& data);
	std::string parseInvoice(const Invoice::Ptr& object);

	LabeledPrice::Ptr parseJsonAndGetLabeledPrice(const boost::property_tree::ptree& data);
	std::string parseLabeledPrice(const LabeledPrice::Ptr& object);

	OrderInfo::Ptr parseJsonAndGetOrderInfo(const boost::property_tree::ptree& data);
	std::string parseOrderInfo(const OrderInfo::Ptr& object);

	PreCheckoutQuery::Ptr parseJsonAndGetPreCheckoutQuery(const boost::property_tree::ptree& data);
	std::string parsePreCheckoutQuery(const PreCheckoutQuery::Ptr& object);

	ShippingAddress::Ptr parseJsonAndGetShippingAddress(const boost::property_tree::ptree& data);
	std::string parseShippingAddress(const ShippingAddress::Ptr& object);

	ShippingOption::Ptr parseJsonAndGetShippingOption(const boost::property_tree::ptree& data);
	std::string parseShippingOption(const ShippingOption::Ptr& object);

	ShippingQuery::Ptr parseJsonAndGetShippingQuery(const boost::property_tree::ptree& data);
	std::string parseShippingQuery(const ShippingQuery::Ptr& object);

	SuccessfulPayment::Ptr parseJsonAndGetSucessfulPayment(const boost::property_tree::ptree& data);
	std::string parseSucessfulPayment(const SuccessfulPayment::Ptr& object);

	inline boost::property_tree::ptree parseJson(const std::string& json) {
		boost::property_tree::ptree tree;
		std::istringstream input(json);
		boost::property_tree::read_json(input, tree);
		return tree;
	}

	template<typename T>
	std::shared_ptr<T> tryParseJson(JsonToTgTypeFunc<T> parseFunc, const boost::property_tree::ptree& data, const std::string& keyName) {
		auto treeItem = data.find(keyName);
		if (treeItem == data.not_found()) {
			return std::shared_ptr<T>();
		}
		return parseFunc(treeItem->second);
	}

	template<typename T>
	std::vector<std::shared_ptr<T>> parseJsonAndGetArray(JsonToTgTypeFunc<T> parseFunc, const boost::property_tree::ptree& data) {
		std::vector<std::shared_ptr<T>> result;
		for (const std::pair<const std::string, boost::property_tree::ptree>& innerTreeItem : data) {
			result.push_back(parseFunc(innerTreeItem.second));
		}
		return result;
	}

	template<typename T>
	std::vector<T> parseJsonAndGetArray(std::function<T(const boost::property_tree::ptree&)> parseFunc, const boost::property_tree::ptree& data, const std::string& keyName) {
		std::vector<T> result;
		auto treeItem = data.find(keyName);
		if (treeItem == data.not_found()) {
			return result;
		}
		for (const std::pair<const std::string, boost::property_tree::ptree>& innerTreeItem : treeItem->second) {
			result.push_back(parseFunc(innerTreeItem.second));
		}
		return result;
	}

	template<typename T>
	std::vector<std::shared_ptr<T>> parseJsonAndGetArray(JsonToTgTypeFunc<T> parseFunc, const boost::property_tree::ptree& data, const std::string& keyName) {
		std::vector<std::shared_ptr<T>> result;
		auto treeItem = data.find(keyName);
		if (treeItem == data.not_found()) {
			return result;
		}
		for (const std::pair<const std::string, boost::property_tree::ptree>& innerTreeItem : treeItem->second) {
			result.push_back(parseFunc(innerTreeItem.second));
		}
		return result;
	}

	template<typename T>
	std::vector<std::vector<std::shared_ptr<T>>> parseJsonAndGet2DArray(JsonToTgTypeFunc<T> parseFunc, const boost::property_tree::ptree& data, const std::string& keyName) {
		std::vector<std::vector<std::shared_ptr<T>>> result;
		auto treeItem = data.find(keyName);
		if (treeItem == data.not_found()) {
			return result;
		}
		for (const std::pair<const std::string, boost::property_tree::ptree>& innerTreeItem : treeItem->second) {
			std::vector<std::shared_ptr<T>> innerResult;
			for (const std::pair<const std::string, boost::property_tree::ptree>& innerInnerTreeItem : innerTreeItem.second) {
				innerResult.push_back(parseFunc(innerInnerTreeItem.second));
			}
			result.push_back(innerResult);
		}
		return result;
	}

	template<typename T>
	std::string parseArray(TgTypeToJsonFunc<T> parseFunc, const std::vector<std::shared_ptr<T>>& objects) {
		if (objects.empty())
			return "";
		std::string result;
		result += '[';
		for (const std::shared_ptr<T>& item : objects) {
			result += parseFunc(item);
			result += ',';
		}
		result.erase(result.length() - 1);
		result += ']';
		return result;
	}

	template<typename T>
	std::string parseArray(std::function<T(const T&)> parseFunc, const std::vector<T>& objects) {
		if (objects.empty())
			return "";
		std::string result;
		result += '[';
		for (const T& item : objects) {
			result += parseFunc(item);
			result += ',';
		}
		result.erase(result.length() - 1);
		result += ']';
		return result;
	}

	template<typename T>
	std::string parse2DArray(TgTypeToJsonFunc<T> parseFunc, const std::vector<std::vector<std::shared_ptr<T>>>& objects) {
		if (objects.empty())
			return "";
		std::string result;
		result += '[';
		for (const std::vector<std::shared_ptr<T>>& item : objects) {
			result += parseArray(parseFunc, item);
			result += ',';
		}
		result.erase(result.length() - 1);
		result += ']';
		return result;
	}

	template<typename T>
	void appendToJson(std::string& json, const std::string& varName, const T& value) {
		if (value == 0) {
			return;
		}
		json += '"';
		json += varName;
		json += "\":";
		json += value;
		json += ',';
	}

	void appendToJson(std::string& json, const std::string& varName, const bool& value) {
		json += '"';
		json += varName;
		json += "\":";
		json += (value ? "true" : "false");
		json += ',';
	}

	void appendToJson(std::string& json, const std::string& varName, const std::string& value);
};

}

#endif //TGBOT_CPP_TGTYPEPARSER_H
