#pragma once
#include <pistache/endpoint.h>
#include <pistache/router.h>

class AnswersHandler {
public:
    void CreateAnswer(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void GetAnswer(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void GetAnswerByQuestionId(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void CreateScore(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void GetScore(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
};