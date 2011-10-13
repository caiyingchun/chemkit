/******************************************************************************
**
** Copyright (C) 2009-2011 Kyle Lutz <kyle.r.lutz@gmail.com>
** All rights reserved.
**
** This file is a part of the chemkit project. For more information
** see <http://www.chemkit.org>.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in the
**     documentation and/or other materials provided with the distribution.
**   * Neither the name of the chemkit project nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
******************************************************************************/

#include "moleculefiletest.h"

#include <chemkit/molecule.h>
#include <chemkit/moleculefile.h>

void MoleculeFileTest::fileName()
{
    chemkit::MoleculeFile file;
    QCOMPARE(file.fileName(), std::string());

    file.setFileName("foo");
    QCOMPARE(file.fileName(), std::string("foo"));

    file.setFileName("bar");
    QCOMPARE(file.fileName(), std::string("bar"));

    file.setFileName(std::string());
    QCOMPARE(file.fileName(), std::string());

    chemkit::MoleculeFile fileWithName("foobar");
    QCOMPARE(fileWithName.fileName(), std::string("foobar"));
}

void MoleculeFileTest::format()
{
    chemkit::MoleculeFile file;
    QVERIFY(file.format() == 0);
}

void MoleculeFileTest::contains()
{
    chemkit::MoleculeFile file;
    QCOMPARE(file.contains(0), false);

    chemkit::Molecule *molecule = new chemkit::Molecule;
    file.addMolecule(molecule);
    QCOMPARE(file.contains(molecule), true);

    chemkit::Molecule *anotherMolecule = new chemkit::Molecule;
    QCOMPARE(file.contains(anotherMolecule), false);

    file.addMolecule(anotherMolecule);
    QCOMPARE(file.contains(anotherMolecule), true);

    file.removeMolecule(molecule);
    QCOMPARE(file.contains(molecule), false);

    file.addMolecule(molecule);
}

void MoleculeFileTest::data()
{
    chemkit::MoleculeFile file;

    file.setData("foo", "bar");
    QCOMPARE(file.data("foo").toString(), std::string("bar"));

    file.setData("number", 4);
    QCOMPARE(file.data("number").toInt(), 4);
}

QTEST_APPLESS_MAIN(MoleculeFileTest)