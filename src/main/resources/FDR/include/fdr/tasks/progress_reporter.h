#pragma once

#include <fstream>
#include <memory>
#include <mutex>

namespace FDR
{
typedef int64_t TaskId;

/// Recieves status reports from FDR about ongoing tasks.
///
/// This class is intended to be subclassed and reports logged appropriately.
///
/// The methods on this class will be called from many different threads, and
/// thus implementers need to take care of any ensuring thread safety.
class ProgressReporter
{
public:
    ProgressReporter();
    virtual ~ProgressReporter();

    enum
    {
        INVALID_TASK = 0,
    };

    /// Actives this progress reporter, subscribing it to any updates.
    ///
    /// This MUST be called from the main thread before ANY other call to
    /// libfdr, other than library_init(), and may only be called once. In
    /// other words, once a ProgressReporter is activated, there is no way
    /// to activate another ProgressReporter.
    ///
    /// If this is overriden, the base class implementation MUST be called.
    virtual void activate();

    /// Deactivates this progress reporter, unsubscribing it from updates.
    ///
    /// This MUST only be called once, after activate().
    ///
    /// If this is overriden, the base class implementation MUST be called.
    virtual void deactivate();

    /// Called when a new task is started.
    ///
    /// @param task_id The new task.
    /// @param parent_task_id The identifier of this task's parent (tasks
    ///     are hierarchical). If there is no parent, this is INVALID_TASK.
    /// @param task_name the name of the task.
    virtual void task_started(TaskId task_id, TaskId parent_task_id, const std::string& task_name);

    /// Called when a new task is finished.
    virtual void task_finished(TaskId task_id);

    /// Called when a task generates a relevant message.
    virtual void task_message_output(TaskId task_id, const std::string& message);

    /// Called when a task's status message has been updated.
    virtual void task_status_updated(TaskId task_id, const std::string& new_status);

private:
    struct Data;
    std::unique_ptr<Data> data;
};

/// A simple progress reporter that logs all progress reports to a file.
class FileProgressReporter : public ProgressReporter
{
public:
    /// Creates a new progress reporter.
    ///
    /// @param file_name The file to write progress reports to.
    FileProgressReporter(const std::string& file_name);

    void activate() override;
    void deactivate() override;
    void task_started(TaskId task_id, TaskId parent_task_id, const std::string& task_name) override;
    void task_finished(TaskId task_id) override;
    void task_message_output(TaskId task_id, const std::string& message) override;
    void task_status_updated(TaskId task_id, const std::string& new_status) override;

private:
    std::mutex mutex;
    std::ofstream stream;
};

/// A progress reporter that sends reports to a stream.
class StreamProgressReporter : public ProgressReporter
{
public:
    enum class StreamIdentifier
    {
        StdOut,
        StdErr,
    };

    StreamProgressReporter(StreamIdentifier output_stream_identifier);

    /// Creates a new StreamProgressReporter.
    ///
    /// @param output_stream The stream to write to. This must be kept
    ///     alive as long as the progress reporter is activated.
    StreamProgressReporter(std::ostream& output_stream);

    void activate() override;
    void deactivate() override;
    void task_started(TaskId task_id, TaskId parent_task_id, const std::string& task_name) override;
    void task_finished(TaskId task_id) override;
    void task_message_output(TaskId task_id, const std::string& message) override;
    void task_status_updated(TaskId task_id, const std::string& new_status) override;

private:
    std::mutex mutex;
    std::ostream& stream;
};

}  // end FDR
