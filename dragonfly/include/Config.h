//
// Config.h - Global configuration parameters for Dragonfly
//

#ifndef __CONFIG_H__
#define __CONFIG_H__

// System includes.
#include <string>

// Engine includes.
#include "Color.h"

namespace df {

////////////////////////////////////////////////////////////
// Compiler warning for deprecated functions and classes
//
// Usage:
//
// class DF_DEPRECATED Class {
//     DF_DEPRECATED void method();
// };
//
// DF_DEPRECATED void function();
//

#if defined(DF_NO_DEPRECATED_WARNINGS)

  // User explicitly requests to disable deprecation warnings.
  #define DF_DEPRECATED

#elif defined(_MSC_VER)

  // Microsoft C++ compiler
  // Note: On newer MSVC versions, using deprecated functions causes
  // compiler error. In order to trigger warning instead of error,
  // compiler flag /sdl- (instead of /sdl) must be specified.
#define DF_DEPRECATED __declspec(deprecated)

#elif defined(__GNUC__)

  // g++ and Clang
#define DF_DEPRECATED __attribute__ ((deprecated))

#else

  // Other compilers are not supported, leave class or function as-is.
  // Sometimes, #pragma directive works, otherwise users get
  // a warning (no error!) for unrecognized #pragma.
#pragma message("DF_DEPRECATED not supported by your compiler")

#define DF_DEPRECATED

#endif
////////////////////////////////////////////////////////////
  
class Config {

 private:
  Config();			 ///< Private since a singleton.
  Config(Config const&);	 ///< Don't allow copy.
  void operator=(Config const&); ///< Don't allow assignment.
  std::string m_config;		 ///< Aggregate string from config file.
  int m_window_horizontal_pixels;///< Horizontal pixels in window.
  int m_window_vertical_pixels;  ///< Vertical pixels in window.
  int m_window_horizontal_chars; ///< Horizontal ASCII spaces in window.
  int m_window_vertical_chars;   ///< Vertical ASCII spaces in window.
  int m_window_style;		 ///< Style of window titlebar.
  enum Color m_window_background_color; ///< Window background color.
  int m_frame_time;		 ///< Target time for 1 game loop (in mlsecs).
  float m_font_scale;		 ///< Font scale multiplier.
  std::string m_window_title;	 ///< Title of window.
  bool m_show_mouse;             ///< True if should show mouse cursor.
  bool m_headless;               ///< True if run without graphics or input.
  std::string m_font_file;	 ///< Filename for graphics fonts.
  std::string m_logfile;	 ///< Filename for dragonfly log.
  int m_random_seed;		 ///< Seed for random number generation.
  bool m_networking;             ///< True if networking enabled.
  int m_quadtree_threshold;      ///< Object threshold for quadtree split.
  int m_quadtree_depth;          ///< Max depth for quadtree.
  int m_grid_width;              ///< Grid width.
  int m_grid_height;             ///< Grid height.
  
 public:
  /// Get the singleton instance of the Config.
  static Config &getInstance();

  /// Get attributes.
  std::string getConfig() const;
  int getWindowHorizontalPixels() const;
  int getWindowVerticalPixels() const;
  int getWindowHorizontalChars() const;
  int getWindowVerticalChars() const;
  enum Color getWindowBackgroundColor() const;
  int getWindowStyle() const;
  int getFrameTime() const;
  float getFontScale() const;
  std::string getWindowTitle() const;
  bool getShowMouse() const;
  bool getHeadless() const;
  std::string getFontFile() const;
  std::string getLogFile() const;
  int getRandomSeed() const;
  bool getNetworking() const;
  int getQuadtreeDepth() const;
  int getQuadtreeThreshold() const;
  int getGridWidth() const;
  int getGridHeight() const;

  /// Match key:value pair in global configuration, returning value.
  /// Return empty string if no match.
  std::string match(std::string find) const;
  
  /// Set attributes.
  void setConfig(std::string config);
  void setWindowHorizontalPixels(int window_horizontal_pixels);
  void setWindowVerticalPixels(int window_vertical_pixels);
  void setWindowHorizontalChars(int window_horizontal_chars);
  void setWindowVerticalChars(int window_vertical_chars);
  void setWindowBackgroundColor(enum Color window_background_color);
  void setWindowStyle(int window_style);
  void setFrameTime(int frame_time);
  void setFontScale(float font_scale);
  void setWindowTitle(std::string window_title);
  void setHeadless(bool headless=true);
  void setShowMouse(bool show_mouse=true);
  void setFontFile(std::string font_file);
  void setLogFile(std::string logfile);
  void setRandomSeed(int random_seed);
  void setNetworking(bool networking);
  void setQuadtreeDepth(int quadtree_thresh);
  void setQuadtreeThreshold(int quadtree_depth);
  void setGridWidth(int grid_width);
  void setGridHeight(int grid_height);
  
  // Write all parameters to logfile.
  void writeToLog() const;

  // Read config paramaters from CONFIG file into string.
  // Format:
  //   Lines beginning with '#' are comments.
  //   Others are:
  //   "variable_1:value_1,"
  //   "variable_2:value_2,"
  //   Variable lines must end with comma (,)
  std::string readConfig();

  // Load config parameters from string.
  // If str is empty, load from file.
  void loadConfig(std::string str="");
};

} // end of namespace df
#endif // __CONFIG_H__
