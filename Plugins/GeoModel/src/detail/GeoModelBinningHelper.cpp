// This file is part of the ACTS project.
//
// Copyright (C) 2016 CERN for the benefit of the ACTS project
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Acts/Plugins/GeoModel/detail/GeoModelBinningHelper.hpp"

#include <numbers>

#include <boost/algorithm/string.hpp>

std::tuple<Acts::DirectedProtoAxis, std::size_t>
Acts::detail::GeoModelBinningHelper::toProtoAxis(
    const std::string& binning, const std::optional<Extent>& extent) {
  std::vector<std::string> binningTokens;
  boost::split(binningTokens, binning, boost::is_any_of(","));
  AxisDirection axisDir = toAxisDirection(binningTokens[0]);

  std::vector<std::string> binningDetails = {binningTokens.begin() + 1,
                                             binningTokens.end()};
  if (binningDetails.size() < 2u) {
    throw std::invalid_argument(
        "GeoModelBinningHelper: Invalid number of binning details, at least "
        "the axis boundary type and the number of bins are needed.");
  }
  AxisBoundaryType boundaryType = AxisBoundaryType::Bound;
  std::string axisBoundaryToken = binningDetails[0];
  if (axisBoundaryToken == "closed") {
    boundaryType = AxisBoundaryType::Closed;
  } else if (axisBoundaryToken != "bound") {
    throw std::invalid_argument(
        "GeoModelBinningHelper: Axis boundary type needs to be closed or "
        "bound.'");
  }
  // The number of bins
  std::size_t nBins = std::stoul(binningDetails[1]);
  // The bin expansion
  std::size_t nExpansion = 0u;
  if (binningDetails.size() > 2u) {
    nExpansion = std::stoul(binningDetails[2]);
  }
  // Bool auto_range
  bool autoRange = true;
  // The Range
  double rangeMin = 0.;
  double rangeMax = 0.;
  if (axisDir == AxisDirection::AxisPhi &&
      boundaryType == AxisBoundaryType::Closed) {
    rangeMin = -std::numbers::pi;
    rangeMax = std::numbers::pi;
  } else {
    if (binningDetails.size() > 3u && binningDetails[3] != "*") {
      autoRange = false;
      rangeMin = std::stod(binningDetails[3]);
    } else if (extent.has_value() && extent.value().constrains(axisDir)) {
      autoRange = false;
      rangeMin = extent.value().min(axisDir);
    } else if (binningDetails[3] != "*") {
      throw std::invalid_argument(
          "GeoModelBinningHelper: Range minimum is not defined.");
    }

    if (binningDetails.size() > 4u && binningDetails[4] != "*") {
      autoRange = false;
      rangeMax = std::stod(binningDetails[4]);
    } else if (extent.has_value() && extent.value().constrains(axisDir)) {
      autoRange = false;
      rangeMax = extent.value().max(axisDir);
    } else if (binningDetails[4] != "*") {
      throw std::invalid_argument(
          "GeoModelBinningHelper: Range maximum is not defined.");
    }
  }
  auto pAxis = autoRange ? DirectedProtoAxis(axisDir, boundaryType, nBins)
                         : DirectedProtoAxis(axisDir, boundaryType, rangeMin,
                                             rangeMax, nBins);
  return {pAxis, nExpansion};
}
