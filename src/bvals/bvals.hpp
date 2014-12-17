#ifndef BOUNDARY_VALUES_HPP
#define BOUNDARY_VALUES_HPP
//======================================================================================
/* Athena++ astrophysical MHD code
 * Copyright (C) 2014 James M. Stone  <jmstone@princeton.edu>
 * See LICENSE file for full public license information.
 *====================================================================================*/
/*! \file bvals.hpp
 *  \brief defines BoundaryValues class used for setting BCs on all data types
 *====================================================================================*/

// Athena headers
#include "../athena.hpp"         // Real
#include "../athena_arrays.hpp"  // AthenaArray

// forward declarations
class MeshBlock;
class Fluid;
class ParameterInput;
struct InterfaceField;

//-------------------- prototypes for all BC functions ---------------------------------

void NeighborInnerX1(MeshBlock *pmb, AthenaArray<Real> &buf);
void NeighborInnerX2(MeshBlock *pmb, AthenaArray<Real> &buf);
void NeighborInnerX3(MeshBlock *pmb, AthenaArray<Real> &buf);
void NeighborOuterX1(MeshBlock *pmb, AthenaArray<Real> &buf);
void NeighborOuterX2(MeshBlock *pmb, AthenaArray<Real> &buf);
void NeighborOuterX3(MeshBlock *pmb, AthenaArray<Real> &buf);

void NeighborInnerX1(MeshBlock *pmb, InterfaceField &buf);
void NeighborInnerX2(MeshBlock *pmb, InterfaceField &buf);
void NeighborInnerX3(MeshBlock *pmb, InterfaceField &buf);
void NeighborOuterX1(MeshBlock *pmb, InterfaceField &buf);
void NeighborOuterX2(MeshBlock *pmb, InterfaceField &buf);
void NeighborOuterX3(MeshBlock *pmb, InterfaceField &buf);

void ReflectInnerX1(MeshBlock *pmb, AthenaArray<Real> &buf);
void ReflectInnerX2(MeshBlock *pmb, AthenaArray<Real> &buf);
void ReflectInnerX3(MeshBlock *pmb, AthenaArray<Real> &buf);
void ReflectOuterX1(MeshBlock *pmb, AthenaArray<Real> &buf);
void ReflectOuterX2(MeshBlock *pmb, AthenaArray<Real> &buf);
void ReflectOuterX3(MeshBlock *pmb, AthenaArray<Real> &buf);

void ReflectInnerX1(MeshBlock *pmb, InterfaceField &buf);
void ReflectInnerX2(MeshBlock *pmb, InterfaceField &buf);
void ReflectInnerX3(MeshBlock *pmb, InterfaceField &buf);
void ReflectOuterX1(MeshBlock *pmb, InterfaceField &buf);
void ReflectOuterX2(MeshBlock *pmb, InterfaceField &buf);
void ReflectOuterX3(MeshBlock *pmb, InterfaceField &buf);

void OutflowInnerX1(MeshBlock *pmb, AthenaArray<Real> &buf);
void OutflowInnerX2(MeshBlock *pmb, AthenaArray<Real> &buf);
void OutflowInnerX3(MeshBlock *pmb, AthenaArray<Real> &buf);
void OutflowOuterX1(MeshBlock *pmb, AthenaArray<Real> &buf);
void OutflowOuterX2(MeshBlock *pmb, AthenaArray<Real> &buf);
void OutflowOuterX3(MeshBlock *pmb, AthenaArray<Real> &buf);

void OutflowInnerX1(MeshBlock *pmb, InterfaceField &buf);
void OutflowInnerX2(MeshBlock *pmb, InterfaceField &buf);
void OutflowInnerX3(MeshBlock *pmb, InterfaceField &buf);
void OutflowOuterX1(MeshBlock *pmb, InterfaceField &buf);
void OutflowOuterX2(MeshBlock *pmb, InterfaceField &buf);
void OutflowOuterX3(MeshBlock *pmb, InterfaceField &buf);

void PeriodicInnerX1(MeshBlock *pmb, AthenaArray<Real> &buf);
void PeriodicInnerX2(MeshBlock *pmb, AthenaArray<Real> &buf);
void PeriodicInnerX3(MeshBlock *pmb, AthenaArray<Real> &buf);
void PeriodicOuterX1(MeshBlock *pmb, AthenaArray<Real> &buf);
void PeriodicOuterX2(MeshBlock *pmb, AthenaArray<Real> &buf);
void PeriodicOuterX3(MeshBlock *pmb, AthenaArray<Real> &buf);

void PeriodicInnerX1(MeshBlock *pmb, InterfaceField &buf);
void PeriodicInnerX2(MeshBlock *pmb, InterfaceField &buf);
void PeriodicInnerX3(MeshBlock *pmb, InterfaceField &buf);
void PeriodicOuterX1(MeshBlock *pmb, InterfaceField &buf);
void PeriodicOuterX2(MeshBlock *pmb, InterfaceField &buf);
void PeriodicOuterX3(MeshBlock *pmb, InterfaceField &buf);

typedef void (*BValFluid_t)(MeshBlock *pmb, AthenaArray<Real> &buf);
typedef void (*BValField_t)(MeshBlock *pmb, InterfaceField &buf);

void InitBoundaryBuffer(int nx1, int nx2, int nx3);

//! \class BoundaryValues
//  \brief BVals data and functions

class BoundaryValues {
public:
  BoundaryValues(MeshBlock *pmb, ParameterInput *pin);
  ~BoundaryValues();

  void StartReceiving(void);
  void LoadAndSendFluidBoundaryBuffer(enum direction dir, AthenaArray<Real> &src);
  bool ReceiveAndSetFluidBoundary(enum direction dir, AthenaArray<Real> &dst);
  void LoadAndSendFieldBoundaryBuffer(enum direction dir, InterfaceField &src);
  bool ReceiveAndSetFieldBoundary(enum direction dir, InterfaceField &dst);

  void EnrollFluidBoundaryFunction (enum direction edge, BValFluid_t  my_bc);
  void EnrollFieldBoundaryFunction(enum direction edge, BValField_t my_bc);

private:
  MeshBlock *pmy_mblock_;  // ptr to MeshBlock containing this BVals

  BValFluid_t FluidBoundary_[6];
  BValField_t FieldBoundary_[6];

  bool fluid_flag_[6][2][2], field_flag_[6][2][2];
  Real *fluid_send_[6];
  Real *fluid_recv_[6];
  Real *field_send_[6];
  Real *field_recv_[6];
};
#endif