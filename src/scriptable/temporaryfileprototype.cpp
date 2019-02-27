/*
    Copyright (c) 2019, Lukas Holecek <hluk@email.cz>

    This file is part of CopyQ.

    CopyQ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    CopyQ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with CopyQ.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "temporaryfileprototype.h"

#include <QScriptEngine>
#include <QScriptValue>
#include <QTemporaryFile>

Q_DECLARE_METATYPE(QTemporaryFile*)

TemporaryFilePrototype::TemporaryFilePrototype(QObject *parent)
    : FilePrototype(parent)
{
}

bool TemporaryFilePrototype::autoRemove() const
{
    const auto v = thisTemporaryFile();
    return v && v->autoRemove();
}

QString TemporaryFilePrototype::fileTemplate() const
{
    const auto v = thisTemporaryFile();
    return v ? v->fileTemplate() : QString();
}

void TemporaryFilePrototype::setAutoRemove(bool autoRemove)
{
    const auto v = thisTemporaryFile();
    if (v)
        v->setAutoRemove(autoRemove);
}

void TemporaryFilePrototype::setFileTemplate(const QScriptValue &name)
{
    const auto v = thisTemporaryFile();
    if (v)
        v->setFileTemplate(name.toString());
}

QTemporaryFile *TemporaryFilePrototype::thisTemporaryFile() const
{
    const auto v = qscriptvalue_cast<QTemporaryFile*>(thisObject().data());
    if (!v && engine() && engine()->currentContext())
        engine()->currentContext()->throwError("Invalid TemporaryFile object");
    return v;
}
