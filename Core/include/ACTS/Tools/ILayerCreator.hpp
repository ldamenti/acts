// This file is part of the ACTS project.
//
// Copyright (C) 2016 ACTS project team
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

///////////////////////////////////////////////////////////////////
// ILayerCreator.h, ACTS project
///////////////////////////////////////////////////////////////////

#ifndef ACTS_GEOMETRYINTERFACES_ILAYERCREATOR_H
#define ACTS_GEOMETRYINTERFACES_ILAYERCREATOR_H 1

// STL
#include <memory>
#include <string>
#include <vector>
#include "ACTS/Utilities/ApproachDescriptor.hpp"
#include "ACTS/Utilities/BinUtility.hpp"

namespace Acts {

class Surface;
class Layer;
typedef std::shared_ptr<const Layer> LayerPtr;
typedef std::shared_ptr<Layer>       MutableLayerPtr;

/// @class ILayerCreator
///
/// Interface class for LayerCreator from DetectorElements
///
class ILayerCreator
{
public:
  /// Virtual destructor
  virtual ~ILayerCreator() {}
  /// ILayerCreator interface method - returning a cylindrical layer
  ///
  /// @param surfaces is the vector of pointers to sensitive surfaces
  /// represented by this layer
  /// @pre the pointers to the sensitive surfaces in the surfaces vectors all
  /// need to be valid, since no check is performed
  /// @param envelopeR is the additional envelope applied in R
  /// @param envelopeZ is the additional envelope applied in z
  /// @param binsRPhi is number of bins the sensitive surfaces are ordered in
  /// phi
  /// @param binsZ is number of bins the sensitive surfaces are ordered in Z
  /// @param transform is the (optional) transform of the layer
  /// @param ad possibility to hand over a specific ApproachDescriptor, which is
  /// needed for material mapping. Otherwise the default ApproachDescriptor will
  /// be taken used for this layer
  ///
  /// @return shared pointer to a newly created layer
  virtual MutableLayerPtr
  cylinderLayer(const std::vector<const Surface*>&  surfaces,
                double                              envelopeR,
                double                              envelopeZ,
                size_t                              binsRPhi,
                size_t                              binsZ,
                std::shared_ptr<Transform3D>        transform = nullptr,
                std::unique_ptr<ApproachDescriptor> ad = nullptr) const = 0;

  /// ILayerCreator interface method - returning a cylindrical layer
  ///
  /// @param surfaces is the vector of pointers to sensitive surfaces
  /// represented by this layer
  /// @pre the pointers to the sensitive surfaces in the surfaces vectors all
  /// need to be valid, since no check is performed
  /// @param layerRmin is the inner radius of the layer
  /// @param layerRmax is the outer radius of the layer
  /// @param layerHalfZ is the half length in z of the layer
  /// @param bTypePhi binning type in phi (equidistant/arbitrary)
  /// @param bTypeZ binning type in z (equidistant/arbitrary)
  /// @param transform is the (optional) transform of the layer
  /// @param ad possibility to hand over a specific ApproachDescriptor, which is
  /// needed for material mapping. Otherwise the default ApproachDescriptor will
  /// be taken used for this layer
  ///
  /// @return shared pointer to a newly created layer
  virtual MutableLayerPtr
  cylinderLayer(const std::vector<const Surface*>&  surfaces,
                double                              layerRmin,
                double                              layerRmax,
                double                              layerHalfZ,
                BinningType                         bTypePhi,
                BinningType                         bTypeZ,
                std::shared_ptr<Transform3D>        transform = nullptr,
                std::unique_ptr<ApproachDescriptor> ad = nullptr) const = 0;

  /// ILayerCreator interface method - returning a cylindrical layer
  ///
  /// @param surfaces is the vector of sensitive surfaces represented by this
  /// layer
  /// @param envelopeR is the additional envelope applied in R
  /// @param envelopeZ is the additional envelope applied in z
  /// @param bTypePhi binning type in phi (equidistant/arbitrary)
  /// @param bTypeZ binning type in z (equidistant/arbitrary)
  /// @param transform is the (optional) transform of the layer
  /// @param ad possibility to hand over a specific ApproachDescriptor, which is
  /// needed for material mapping. Otherwise the default ApproachDescriptor will
  /// be taken used for this layer
  ///
  /// @return shared pointer to a newly created layer
  virtual MutableLayerPtr
  cylinderLayer(const std::vector<const Surface*>&  surfaces,
                double                              envelopeR,
                double                              envelopeZ,
                BinningType                         bTypePhi,
                BinningType                         bTypeZ,
                std::shared_ptr<Transform3D>        transform = nullptr,
                std::unique_ptr<ApproachDescriptor> ad = nullptr) const = 0;

  /// ILayerCreator interface method - returning a disc layer
  ///
  /// @param surfaces is the vector of pointers to sensitive surfaces
  /// represented by this layer
  /// @pre the pointers to the sensitive surfaces in the surfaces vectors all
  /// need to be valid, since no check is performed
  /// @param envelopeMinR is the additional envelope applied in R at Rmin
  /// @param envelopeMaxR is the additional envelope applied in R in Rmax
  /// @param envelopeZ is the additional envelope applied in z
  /// @param binsR is number of bins the sensitive surfaces are ordered in R
  /// @param binsPhi is number of bins the sensitive surfaces are ordered in Phi
  /// @param transform is the (optional) transform of the layer
  /// @param ad possibility to hand over a specific ApproachDescriptor, which is
  /// needed for material mapping. Otherwise the default ApproachDescriptor will
  /// be taken used for this layer
  ///
  /// @return shared pointer to a newly created layer
  virtual MutableLayerPtr
  discLayer(const std::vector<const Surface*>&  surfaces,
            double                              envelopeMinR,
            double                              envelopeMaxR,
            double                              envelopeZ,
            size_t                              binsR,
            size_t                              binsPhi,
            std::shared_ptr<Transform3D>        transform = nullptr,
            std::unique_ptr<ApproachDescriptor> ad = nullptr) const = 0;

  /// ILayerCreator interface method - returning a disc layer
  ///
  /// @param surfaces is the vector of pointers to sensitive surfaces
  /// represented by this layer
  /// @pre the pointers to the sensitive surfaces in the surfaces vectors all
  /// need to be valid, since no check is performed
  /// @param layerRmin is the inner radius of the layer
  /// @param layerRmax is the outer radius of the layer
  /// @param layerZmin is the minimum in z of the layer
  /// @param layerZmax is the maximum in z of the layer
  /// @param bTypeR binning type in r (equidistant/arbitrary)
  /// @param bTypePhi binning type in phi (equidistant/arbitrary)
  /// @param transform is the (optional) transform of the layer
  /// @param ad possibility to hand over a specific ApproachDescriptor, which is
  /// needed for material mapping. Otherwise the default ApproachDescriptor will
  /// be taken used for this layer
  ///
  /// @return shared pointer to a newly created layer
  virtual MutableLayerPtr
  discLayer(const std::vector<const Surface*>&  surfaces,
            double                              layerZmin,
            double                              layerZmax,
            double                              layerRmin,
            double                              layerRmax,
            BinningType                         bTypeR,
            BinningType                         bTypePhi,
            std::shared_ptr<Transform3D>        transform = nullptr,
            std::unique_ptr<ApproachDescriptor> ad = nullptr) const = 0;

  /// ILayerCreator interface method - returning a disc layer
  ///
  /// @param surfaces is the vector of sensitive surfaces represented by this
  /// layer
  /// @param envelopeMinR is the additional envelope applied in R at Rmin
  /// @param envelopeMaxR is the additional envelope applied in R in Rmax
  /// @param envelopeZ is the additional envelope applied in z
  /// @param bTypeR binning type in r (equidistant/arbitrary)
  /// @param bTypePhi binning type in phi (equidistant/arbitrary)
  /// @param transform is the (optional) transform of the layer
  /// @param ad possibility to hand over a specific ApproachDescriptor, which is
  /// needed for material mapping. Otherwise the default ApproachDescriptor will
  /// be taken used for this layer
  ///
  /// @return shared pointer to a newly created layer
  virtual MutableLayerPtr
  discLayer(const std::vector<const Surface*>&  surfaces,
            double                              envelopeMinR,
            double                              envelopeMaxR,
            double                              envelopeZ,
            BinningType                         bTypeR,
            BinningType                         bTypePhi,
            std::shared_ptr<Transform3D>        transform = nullptr,
            std::unique_ptr<ApproachDescriptor> ad = nullptr) const = 0;

  /// ILayerCreator interface method - returning a plane layer
  ///
  /// @param surfaces is the vector of pointers to sensitive surfaces
  /// represented by this layer
  /// @pre the pointers to the sensitive surfaces in the surfaces vectors all
  /// need to be valid, since no check is performed
  /// @param envelopeXY is the additional envelope applied in XY
  /// @param envelopeZ is the additional envelope applied in Z
  /// @param binsX is number of bins the sensitive surfaces are ordered in X
  /// @param binsY is number of bins the sensitive surfaces are ordered in Y
  /// @param transform is the (optional) transform of the layer
  /// @param ad possibility to hand over a specific ApproachDescriptor, which is
  /// needed for material mapping. Otherwise the default ApproachDescriptor will
  /// be taken used for this layer
  ///
  /// @return shared pointer to a newly created layer
  virtual MutableLayerPtr
  planeLayer(const std::vector<const Surface*>&  surfaces,
             double                              envelopeXY,
             double                              envelopeZ,
             size_t                              binsX,
             size_t                              binsY,
             std::shared_ptr<Transform3D>        transform = nullptr,
             std::unique_ptr<ApproachDescriptor> ad = nullptr) const = 0;
};

}  // end of namespace

#endif  // ACTS_GEOMETRYINTERFACES_ILAYERCREATOR_H
