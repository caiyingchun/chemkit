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
** DATA, OR PROFITS; OR BUSINESS INTERRchemkitUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
******************************************************************************/

#ifndef CHEMKIT_FORCEFIELD_H
#define CHEMKIT_FORCEFIELD_H

#include "md.h"

#include <string>
#include <vector>

#include <chemkit/point3.h>
#include <chemkit/vector3.h>

#include "forcefieldatom.h"
#include "forcefieldcalculation.h"

namespace chemkit {

class Atom;
class Molecule;

namespace md {

class ForceFieldPrivate;

class CHEMKIT_MD_EXPORT ForceField
{
public:
    // enumerations
    enum Flag {
        AnalyticalGradient = 0x01
    };

    // typedefs
    typedef ForceField* (*CreateFunction)();

    // construction and destruction
    virtual ~ForceField();

    // properties
    std::string name() const;
    int flags() const;
    int size() const;
    std::vector<ForceFieldAtom *> atoms() const;
    int atomCount() const;
    ForceFieldAtom* atom(int index) const;
    ForceFieldAtom* atom(const Atom *atom) const;

    // setup
    void addMolecule(const Molecule *molecule);
    void removeMolecule(const Molecule *molecule);
    std::vector<const Molecule *> molecules() const;
    int moleculeCount() const;
    virtual bool setup();
    bool isSetup() const;
    virtual void clear();

    // parameters
    void setParameterSet(const std::string &name);
    std::string parameterSet() const;
    std::vector<std::string> parameterSets() const;
    void setParameterFile(const std::string &fileName);
    std::string parameterFile() const;

    // calculations
    std::vector<ForceFieldCalculation *> calculations() const;
    int calculationCount() const;
    virtual Real energy() const;
    std::vector<Vector3> gradient() const;
    std::vector<Vector3> numericalGradient() const;
    Real largestGradient() const;
    Real rootMeanSquareGradient() const;

    // coordinates
    void readCoordinates(const Molecule *molecule);
    void readCoordinates(const Atom *atom);
    void writeCoordinates(Molecule *molecule) const;
    void writeCoordinates(Atom *atom) const;

    // energy minimization
    bool minimizationStep(Real converganceValue = 0.1);

    // geometry
    Real distance(const ForceFieldAtom *a, const ForceFieldAtom *b) const;
    Real bondAngle(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c) const;
    Real bondAngleRadians(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c) const;
    Real torsionAngle(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c, const ForceFieldAtom *d) const;
    Real torsionAngleRadians(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c, const ForceFieldAtom *d) const;
    Real wilsonAngle(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c, const ForceFieldAtom *d) const;
    Real wilsonAngleRadians(const ForceFieldAtom *a, const ForceFieldAtom *b, const ForceFieldAtom *c, const ForceFieldAtom *d) const;

    // error handling
    std::string errorString() const;

    // static methods
    static ForceField* create(const std::string &name);
    static std::vector<std::string> forceFields();

protected:
    ForceField(const std::string &name);
    void setFlags(int flags);
    void addAtom(ForceFieldAtom *atom);
    void removeAtom(ForceFieldAtom *atom);
    void addCalculation(ForceFieldCalculation *calculation);
    void removeCalculation(ForceFieldCalculation *calculation);
    void setCalculationSetup(ForceFieldCalculation *calculation, bool setup);
    void addParameterSet(const std::string &name, const std::string &fileName);
    void removeParameterSet(const std::string &name);
    void setErrorString(const std::string &errorString);

private:
    ForceFieldPrivate* const d;
};

} // end md namespace
} // end chemkit namespace

#endif // CHEMKIT_FORCEFIELD_H