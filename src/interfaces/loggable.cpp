#include "loggable.h"

void Loggable::_set_dir(Date date)
{
        memset(_dir, 0, sizeof(_dir));  // prevent overlapping strings
        sprintf(
                _dir, "/%04d%02d%02d",
                date.get_year(), date.get_month(), date.get_day()
        );
}

void Loggable::_set_filename(Time time, const char *extension)
{
        memset(_filename, 0, sizeof(_filename));  // prevent overlapping strings
        sprintf(
                _filename, "/%02d%02d%02d.%s",
                time.get_hour(), time.get_minute(), time.get_second(), extension
        );
}

void Loggable::_set_path(char *_dir, char *_filename)
{
        memset(_path, 0, sizeof(_path));  // prevent overlapping strings
        sprintf(_path, "%s%s", _dir, _filename);
}

char *Loggable::get_dir()
{
        return _dir;
}

char *Loggable::get_path()
{
        return _path;
}

char *Loggable::get_log()
{
        return _log;
}

size_t Loggable::get_size()
{
        return _log_size;
}

void Loggable::reset()
{
        memset(_log,      0, sizeof(_log));
        memset(_dir,      0, sizeof(_dir));
        memset(_path,     0, sizeof(_path));
        memset(_filename, 0, sizeof(_filename));
        _log_size = 0;
}
