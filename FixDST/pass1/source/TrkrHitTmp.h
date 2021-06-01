/**
 * @file trackbase/TrkrHitTmp.h
 * @author D. McGlinchey
 * @date 4 June 2018
 * @brief Base class for hit object
 */
#ifndef TRACKBASE_TRKRHITTMP_H
#define TRACKBASE_TRKRHITTMP_H

#include <phool/PHObject.h>

#include <iostream>

/**
 * @brief Base class for hit object
 *
 * This is the empyt virtual base class for a hit object.
 * Each subsystem should implement an inherited version
 * which contains the actual storage information.
 */
class TrkrHitTmp : public PHObject
{
 public:
  enum HitType {intthit = 0, mvtxhit = 1, tpchit = 2, micromegashit = 3};

  //! ctor
  TrkrHitTmp(); 

  //! dtor
  virtual ~TrkrHitTmp() {}
  // PHObject virtual overloads
  virtual void identify(std::ostream& os = std::cout) const
  {
    os << "TrkrHitTmp base class" << std::endl;
  }
  virtual void Reset() {}
  virtual int isValid() const { return 0; }

  void addEnergy(const double edep) {m_edep += edep;}
  double getEnergy() {return m_edep;}
  void setAdc(const unsigned int adc) {m_adc = adc;}
  unsigned int getAdc() { return m_adc;}
  void set_hittype(const int i) {m_HitType = i;}
  int get_hittype() const {return m_HitType;}
 protected:
  double m_edep = 0.;
  unsigned int m_adc = 0;
  int m_HitType = -1;
  ClassDef(TrkrHitTmp, 1);
};

#endif //TRACKBASE_TRKRHITTMP_H
