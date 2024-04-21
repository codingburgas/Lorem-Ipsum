#include "shema.hpp"

void createShema(soci::session* sql) 
{
    *sql << std::string(R"(
-- public.users definition
-- Drop table
-- DROP TABLE public.users;
CREATE TABLE public.users (
	id int4 GENERATED ALWAYS AS IDENTITY( INCREMENT BY 1 MINVALUE 1 MAXVALUE 2147483647 START 1 CACHE 1 NO CYCLE) NOT NULL,
	"name" varchar(250) NOT NULL,
	username varchar(250) NOT NULL,
	email varchar(250) NOT NULL,
	country varchar(100) NOT NULL,
	password_hash varchar(300) NOT NULL,
	CONSTRAINT users_pk PRIMARY KEY (id),
	CONSTRAINT users_unique UNIQUE (username),
	CONSTRAINT users_unique_1 UNIQUE (email)
);
-- public.badges definition
-- Drop table
-- DROP TABLE public.badges;
CREATE TABLE public.badges (
	id int4 GENERATED ALWAYS AS IDENTITY NOT NULL,
	title varchar(250) NOT NULL,
	color varchar(250) NOT NULL,
	image varchar(500) NOT NULL,
	CONSTRAINT badges_pk PRIMARY KEY (id)
);
-- public.notifications definition
-- Drop table
-- DROP TABLE public.notifications;
CREATE TABLE public.notifications (
	user_id int4 GENERATED ALWAYS AS IDENTITY NOT NULL,
	title varchar(250) NOT NULL,
	info varchar(600) NOT NULL,
	CONSTRAINT notifications_pk PRIMARY KEY (user_id)
);
-- public.questions definition
-- Drop table
-- DROP TABLE public.questions;
CREATE TABLE public.questions (
	id int4 GENERATED ALWAYS AS IDENTITY NOT NULL,
	question varchar(300) NOT NULL,
	answer varchar(300) NOT NULL,
	answer_a varchar(300) NOT NULL,
	answer_b varchar(300) NOT NULL,
	answer_c varchar(300) NOT NULL,
	answer_d varchar(300) NOT NULL,
	CONSTRAINT questions_pk PRIMARY KEY (id)
);

-- public.organisations definition
-- Drop table
-- DROP TABLE public.organisations;
CREATE TABLE public.organisations (
	id int4 GENERATED ALWAYS AS IDENTITY( INCREMENT BY 1 MINVALUE 1 MAXVALUE 2147483647 START 1 CACHE 1 NO CYCLE) NOT NULL,
	"name" varchar(250) NOT NULL,
	"code" varchar(250) NOT NULL,
	owner_id int4 NOT NULL,
	CONSTRAINT organisations_pk PRIMARY KEY (id),
	CONSTRAINT organisations_users_fk FOREIGN KEY (owner_id) REFERENCES public.users(id) ON DELETE CASCADE ON UPDATE CASCADE
);
-- public.organisations_users definition
-- Drop table
-- DROP TABLE public.organisations_users;
CREATE TABLE public.organisations_users (
	user_id int4 NOT NULL,
	organisation_id int4 NOT NULL,
	"role" varchar(250) NOT NULL,
	CONSTRAINT organisations_users_pkey PRIMARY KEY (user_id, organisation_id),
	CONSTRAINT organisations_users_organisations_fk FOREIGN KEY (organisation_id) REFERENCES public.organisations(id) ON DELETE CASCADE ON UPDATE CASCADE,
	CONSTRAINT organisations_users_users_fk FOREIGN KEY (user_id) REFERENCES public.users(id) ON DELETE CASCADE ON UPDATE CASCADE
);

-- public.stats definition
-- Drop table
-- DROP TABLE public.stats;
CREATE TABLE public.stats (
	id int4 GENERATED ALWAYS AS IDENTITY( INCREMENT BY 1 MINVALUE 1 MAXVALUE 2147483647 START 1 CACHE 1 NO CYCLE) NOT NULL,
	course_id int4 NOT NULL,
	highest_student_id int4 NOT NULL,
	lowest_student_id int4 NOT NULL,
	course_score float8 NOT NULL,
	CONSTRAINT stats_pk PRIMARY KEY (id),
	CONSTRAINT stats_users_fk FOREIGN KEY (highest_student_id) REFERENCES public.users(id) ON DELETE CASCADE ON UPDATE CASCADE,
	CONSTRAINT stats_users_fk_1 FOREIGN KEY (lowest_student_id) REFERENCES public.users(id) ON DELETE CASCADE ON UPDATE CASCADE
);
-- public.users_badges definition
-- Drop table
-- DROP TABLE public.users_badges;
CREATE TABLE public.users_badges (
	user_id int4 NOT NULL,
	badge_id int4 NOT NULL,
	CONSTRAINT users_badges_pkey PRIMARY KEY (user_id, badge_id),
	CONSTRAINT users_badges_badges_fk FOREIGN KEY (badge_id) REFERENCES public.badges(id) ON DELETE CASCADE ON UPDATE CASCADE,
	CONSTRAINT users_badges_users_fk FOREIGN KEY (user_id) REFERENCES public.users(id) ON DELETE CASCADE ON UPDATE CASCADE
);
-- public.courses definition
-- Drop table
-- DROP TABLE public.courses;
CREATE TABLE public.courses (
	id int4 GENERATED ALWAYS AS IDENTITY NOT NULL,
	owner_id int4 NOT NULL,
	organisation_id int4 NOT NULL,
	"name" varchar(250) NOT NULL,
	"code" varchar(250) NOT NULL,
	subject varchar(300) NOT NULL,
	CONSTRAINT course_pk PRIMARY KEY (id),
	CONSTRAINT course_organisations_fk FOREIGN KEY (organisation_id) REFERENCES public.organisations(id) ON DELETE CASCADE ON UPDATE CASCADE,
	CONSTRAINT course_users_fk FOREIGN KEY (owner_id) REFERENCES public.users(id) ON DELETE CASCADE ON UPDATE CASCADE
);
-- public.themes definition
-- Drop table
-- DROP TABLE public.themes;
CREATE TABLE public.themes (
	id int4 GENERATED ALWAYS AS IDENTITY( INCREMENT BY 1 MINVALUE 1 MAXVALUE 2147483647 START 1 CACHE 1 NO CYCLE) NOT NULL,
	course_id int4 NOT NULL,
	title varchar(250) NOT NULL,
	info varchar(3000) NOT NULL,
	CONSTRAINT theme_pk PRIMARY KEY (id),
	CONSTRAINT course_fk FOREIGN KEY (course_id) REFERENCES public.courses(id) ON DELETE CASCADE ON UPDATE CASCADE
);
-- public.tests definition
-- Drop table
-- DROP TABLE public.tests;
CREATE TABLE public.tests (
	id int4 GENERATED ALWAYS AS IDENTITY NOT NULL,
	title varchar(250) NOT NULL,
	theme_id int4 NOT NULL,
	CONSTRAINT tests_pk PRIMARY KEY (id),
	CONSTRAINT test_themes_fk FOREIGN KEY (theme_id) REFERENCES public.themes(id) ON DELETE CASCADE ON UPDATE CASCADE
);
-- public.questions_tests definition
-- Drop table
-- DROP TABLE public.questions_tests;
CREATE TABLE public.questions_tests (
	question_id int4 NOT NULL,
	test_id int4 NOT NULL,
	CONSTRAINT question_tests_pkey PRIMARY KEY (question_id, test_id),
	CONSTRAINT questions_tests_questions_fk FOREIGN KEY (question_id) REFERENCES public.questions(id) ON DELETE CASCADE ON UPDATE CASCADE,
	CONSTRAINT questions_tests_tests_fk FOREIGN KEY (test_id) REFERENCES public.tests(id) ON DELETE CASCADE ON UPDATE CASCADE
);

-- public.scores definition
-- Drop table
-- DROP TABLE public.scores;
CREATE TABLE public.scores (
	test_id int4 NOT NULL,
	user_id int4 NOT NULL,
	score float8 NOT NULL,
	CONSTRAINT scores_pkey PRIMARY KEY (test_id, user_id),
	CONSTRAINT scores_tests_fk FOREIGN KEY (test_id) REFERENCES public.tests(id) ON DELETE CASCADE ON UPDATE CASCADE,
	CONSTRAINT scores_users_fk FOREIGN KEY (user_id) REFERENCES public.users(id) ON DELETE CASCADE ON UPDATE CASCADE
);
-- public.themes_tests definition
-- Drop table
-- DROP TABLE public.themes_tests;
CREATE TABLE public.themes_tests (
	theme_id int4 NOT NULL,
	test_id int4 NOT NULL,
	CONSTRAINT themes_tests_pkey PRIMARY KEY (theme_id, test_id),
	CONSTRAINT themes_tests_tests_fk FOREIGN KEY (test_id) REFERENCES public.tests(id) ON DELETE CASCADE ON UPDATE CASCADE,
	CONSTRAINT themes_tests_themes_fk FOREIGN KEY (theme_id) REFERENCES public.themes(id) ON DELETE CASCADE ON UPDATE CASCADE
);
-- public.courses_scores definition
-- Drop table
-- DROP TABLE public.courses_scores;
CREATE TABLE public.courses_scores (
	id int4 GENERATED ALWAYS AS IDENTITY NOT NULL,
	user_id int4 NOT NULL,
	score float8 NOT NULL,
	course_id int4 NOT NULL,
	"position" int4 NOT NULL,
	CONSTRAINT courses_scores_pk PRIMARY KEY (id),
	CONSTRAINT courses_scores_course_fk FOREIGN KEY (course_id) REFERENCES public.courses(id) ON DELETE CASCADE ON UPDATE CASCADE,
	CONSTRAINT courses_scores_users_fk FOREIGN KEY (user_id) REFERENCES public.users(id) ON DELETE CASCADE ON UPDATE CASCADE
);
-- public.organisations_courses definition
-- Drop table
-- DROP TABLE public.organisations_courses;
CREATE TABLE public.organisations_courses (
	course_id int4 NOT NULL,
	organisation_id int4 NOT NULL,
	CONSTRAINT organisations_courses_pkey PRIMARY KEY (course_id, organisation_id),
	CONSTRAINT organisations_courses_course_fk FOREIGN KEY (course_id) REFERENCES public.courses(id) ON DELETE CASCADE ON UPDATE CASCADE,
	CONSTRAINT organisations_courses_organisations_fk FOREIGN KEY (organisation_id) REFERENCES public.organisations(id) ON DELETE CASCADE ON UPDATE CASCADE
);
-- public.users_courses definition
-- Drop table
-- DROP TABLE public.users_courses;
CREATE TABLE public.users_courses (
	user_id int4 NOT NULL,
	course_id int4 NOT NULL,
	user_role varchar(200) NOT NULL,
	CONSTRAINT users_courses_pkey PRIMARY KEY (user_id, course_id),
	CONSTRAINT users_courses_courses_fk FOREIGN KEY (course_id) REFERENCES public.courses(id) ON DELETE CASCADE ON UPDATE CASCADE,
	CONSTRAINT users_courses_users_fk FOREIGN KEY (user_id) REFERENCES public.users(id) ON DELETE CASCADE ON UPDATE CASCADE
);
    )");
}