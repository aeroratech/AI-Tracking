#ifndef __YOLOV5S_H__
#define __YOLOV5S_H__

#include <functional>
#include <memory>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

#include "byteTrack.hpp"
#include "utils.h"

namespace yolov5 {

/**
 * @brief: Object detection result structure.
 */

/**
 * @brief: Custom Pre-Process/Post-Process function objects, not support yet.
 */
typedef std::function<bool(const cv::Mat& frame)> pre_process_t;
typedef std::function<bool(std::vector<ObjectData>& results)> post_process_t;

/**
 * @brief: Object detection instance.
 */
class EXPORT_API ObjectDetection {
 public:
  /**
   * @brief: Constructor.
   * @Author: Ricardo Lu
   * @param {*}
   * @return {*}
   */
  ObjectDetection();

  /**
   * @brief: Deconstructor.
   * @Author: Ricardo Lu
   * @param {*}
   * @return {*}
   */
  ~ObjectDetection();

  /**
   * @brief: Init a object detection instance, must be called before inference.
   * @Author: Ricardo Lu
   * @param {std::string&} model_path: Absolute path of model file.
   * @param {runtime_t} runtime: Inference hardware runtime.
   * @return {bool} true if init successfully, false if failed.
   */
  bool Init(const ObjectDetectionConfig& config);

  /**
   * @brief: Release relevant resources.
   * @Author: Ricardo Lu
   * @param {*}
   * @return {*}
   */
  bool Deinit();

  /**
   * @brief: Balance the accuracy and recall.
   * Setting these to a higher value can be used to improve verification
   * accuracy. But the recall might be reduced. It means some fuzzy objects
   * might not be detected. You can change any threshold any time, no matter
   * whether it is initialized or running.
   * @Author: Ricardo Lu
   * @param {float&} conf_thresh: Confidence threshold of inference output
   * probability.
   * @param {float&} nms_thresh: Threshold of NMS task, [0.0f, 1.0f]
   * @return {bool} true if setter successfully, false if failed.
   */
  bool SetScoreThreshold(const float& conf_thresh, const float& nms_thresh);

  /**
   * @brief: Set up monitoring area. The whole image is used as the monitoring
   * area, if ROI is not set.
   * @Author: Ricardo Lu
   * @param {cv::Rect&} Monitoring interested region.
   * @return {bool} true if setter successfully, false if failed.
   */
  bool SetROI(const cv::Rect& roi);

  /**
   *  @brief Register pre-process function
   *  @param[in] func   User custom pre-process function.
   *  @retval    true   Register successful.
   *  @retval    false  Register failed.
   */
  bool RegisterPreProcess(pre_process_t func);

  /**
   *  @brief Register post-process function
   *  @param[in] func   User custom post-process function.
   *  @retval    true   Register successful.
   *  @retval    false  Register failed.
   */
  bool RegisterPreProcess(post_process_t func);

  /**
   * @brief: Core method of object detection.
   * @Author: Ricardo Lu
   * @param {cv::Mat&} image: A RGB format image needs to be detected.
   * @param {std::vector<std::vector<ts::ObjectData> >&} results: Detection
   * results vector for each image.
   * @return {bool} true if detect successfullly, false if failed.
   */
  bool Detect(cv::Mat& image, std::vector<ObjectData>& results);

  /**
   * @brief: Check object detection instance initialization state.
   * @Author: Ricardo Lu
   * @return {bool} true if initialized, false if not.
   */
  bool IsInitialized();

  std::shared_ptr<BYTETracker> tracker_{nullptr};

 private:
  // object detection handler: all methods of ObjectDetection will be forward to
  // it.
  void* impl = nullptr;
};

}  // namespace yolov5

#endif  // __YOLOV5S_H__
