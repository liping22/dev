/*
 *  Copyright (c) 2013-2014, Filippo Basso <bassofil@dei.unipd.it>
 *
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *     1. Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *     2. Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *     3. Neither the name of the copyright holder(s) nor the
 *        names of its contributors may be used to endorse or promote products
 *        derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 *  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CALIBRATION_COMMON_DEPTH_SENSOR_H_
#define CALIBRATION_COMMON_DEPTH_SENSOR_H_

#include <boost/make_shared.hpp>
#include <calibration_common/base/math.h>
#include <calibration_common/depth/undistortion_model.h>
#include <calibration_common/objects/sensor.h>
#include <calibration_common/depth/traits.h>

namespace calibration
{

template <typename DepthT_>
  class DepthSensor : public Sensor
  {
  public:

    typedef boost::shared_ptr<DepthSensor> Ptr;
    typedef boost::shared_ptr<const DepthSensor> ConstPtr;

    typedef DepthUndistortionModel<DepthT_> UndistortionModel;

    DepthSensor()
      : Sensor(),
        undistortion_model_(boost::make_shared<NoUndistortion_<DepthT_> >()),
        depth_error_function_(Vector3::Zero())
    {
      // Do nothing
    }

    const typename UndistortionModel::ConstPtr undistortionModel() const
    {
      return undistortion_model_;
    }

    void setUndistortionModel(const typename UndistortionModel::ConstPtr & undistortion_model)
    {
      undistortion_model_ = undistortion_model;
    }

    const Polynomial<Scalar, 2> depthErrorFunction() const
    {
      return depth_error_function_;
    }

    void setDepthErrorFunction(const Polynomial<Scalar, 2> & depth_error_function)
    {
      depth_error_function_ = depth_error_function;
    }

  private:

    typename UndistortionModel::ConstPtr undistortion_model_;
    Polynomial<Scalar, 2> depth_error_function_;

  };

template <typename ScalarT_>
  struct DepthSensorEigen_ : public DepthSensor<DepthEigen_<ScalarT_> >
  {
    typedef boost::shared_ptr<DepthSensorEigen_> Ptr;
    typedef boost::shared_ptr<const DepthSensorEigen_> ConstPtr;
  };

template <typename PCLPointT_>
  struct DepthSensorPCL_ : public DepthSensor<DepthPCL_<PCLPointT_> >
  {
    typedef boost::shared_ptr<DepthSensorPCL_> Ptr;
    typedef boost::shared_ptr<const DepthSensorPCL_> ConstPtr;
  };

typedef DepthSensor<DepthEigen> DepthSensorEigen;
typedef DepthSensor<DepthPCL> DepthSensorPCL;

//class DepthSensorEigen : public Sensor
//{
//public:
//
//  typedef boost::shared_ptr<DepthSensorEigen> Ptr;
//  typedef boost::shared_ptr<const DepthSensorEigen> ConstPtr;
//
//  typedef DepthUndistortionModel<UndTraitsEigen<Scalar> > UndistortionModel;
//
//  DepthSensorEigen()
//    : Sensor(),
//      undistortion_model_(boost::make_shared<NoUndistortionEigen<Scalar> >()),
//      depth_error_function_(Vector3::Zero())
//  {
//    // Do nothing
//  }
//
//  const typename UndistortionModel::ConstPtr undistortionModel() const
//  {
//    return undistortion_model_;
//  }
//
//  void setUndistortionModel(const typename UndistortionModel::ConstPtr & undistortion_model)
//  {
//    undistortion_model_ = undistortion_model;
//  }
//
//  const Polynomial<Scalar, 2> depthErrorFunction() const
//  {
//    return depth_error_function_;
//  }
//
//  void setDepthErrorFunction(const Polynomial<Scalar, 2> & depth_error_function)
//  {
//    depth_error_function_ = depth_error_function;
//  }
//
//private:
//
//  typename UndistortionModel::ConstPtr undistortion_model_;
//  Polynomial<Scalar, 2> depth_error_function_;
//
//};
//
//template <typename PCLPoint_>
//  class DepthSensorPCL : public Sensor
//  {
//  public:
//
//    typedef boost::shared_ptr<DepthSensorPCL> Ptr;
//    typedef boost::shared_ptr<const DepthSensorPCL> ConstPtr;
//
//    typedef DepthUndistortionModel<UndTraitsPCL<Scalar, PCLPoint_> > UndistortionModel;
//
//    DepthSensorPCL()
//      : Sensor(),
//        undistortion_model_(boost::make_shared<NoUndistortionPCL<Scalar, PCLPoint_> >()),
//        depth_error_function_(Vector3::Zero())
//    {
//      // Do nothing
//    }
//
//    const typename UndistortionModel::ConstPtr undistortionModel() const
//    {
//      return undistortion_model_;
//    }
//
//    void setUndistortionModel(const typename UndistortionModel::ConstPtr & undistortion_model)
//    {
//      undistortion_model_ = undistortion_model;
//    }
//
//    const Polynomial<Scalar, 2> depthErrorFunction() const
//    {
//      return depth_error_function_;
//    }
//
//    void setDepthErrorFunction(const Polynomial<Scalar, 2> & depth_error_function)
//    {
//      depth_error_function_ = depth_error_function;
//    }
//
//  private:
//
//    typename UndistortionModel::ConstPtr undistortion_model_;
//    Polynomial<Scalar, 2> depth_error_function_;
//
//  };

} /* namespace calibration */
#endif /* CALIBRATION_COMMON_SENSOR_H_ */
