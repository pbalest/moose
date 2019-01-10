//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef ADSTRESSDIVERGENCETENSORS_H
#define ADSTRESSDIVERGENCETENSORS_H

#include "ADKernel.h"

// Forward Declarations
template <ComputeStage>
class ADStressDivergenceTensors;
template <typename>
class RankTwoTensorTempl;
typedef RankTwoTensorTempl<Real> RankTwoTensor;
typedef RankTwoTensorTempl<ADReal> ADRankTwoTensor;

declareADValidParams(ADStressDivergenceTensors);

/**
 * ADStressDivergenceTensors is the automatic differentiation version of StressDivergenceTensors
 */
template <ComputeStage compute_stage>
class ADStressDivergenceTensors : public ADKernel<compute_stage>
{
public:
  ADStressDivergenceTensors(const InputParameters & parameters);

protected:
  virtual void initialSetup() override;

  virtual ADResidual computeQpResidual() override;
  virtual void precalculateResidual() override;

  const std::string _base_name;

  const ADMaterialProperty(RankTwoTensor) & _stress;
  const unsigned int _component;

  /// Coupled displacement variables
  const unsigned int _ndisp;
  std::vector<unsigned int> _disp_var;

  /// Gradient of test function averaged over the element. Used in volumetric locking correction calculation.
  std::vector<typename RealVectorValueType<compute_stage>::type> _avg_grad_test;

  /// Flag for volumetric locking correction
  const bool _volumetric_locking_correction;

  usingKernelMembers;
};

#endif // ADSTRESSDIVERGENCETENSORS_H
