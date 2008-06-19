#ifndef MAIN_H_
#define MAIN_H_

#define NDEBUG
#include <fileref.h>
#include <tag.h>
#include <mpegfile.h>
#include <id3v2tag.h>

#ifdef AUDIERE
#include <audiere.h>
#endif

// convert QString to TagLib::String and vice verse
#define QS(s) QString::fromUtf8(s.toCString(true))
#define TS(s) TagLib::String(s.toUtf8().constData(), TagLib::String::UTF8)

#endif /*MAIN_H_*/
