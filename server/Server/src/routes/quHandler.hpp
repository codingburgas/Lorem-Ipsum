#pragma once
#include <pistache/endpoint.h>
#include <pistache/router.h>

class QuestionHandler {
public:
    void CreateQuestion(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void GetQuestion(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void GetQuestions(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
};