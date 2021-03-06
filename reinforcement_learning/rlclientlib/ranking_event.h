#pragma once
#include <string>

namespace reinforcement_learning {
  namespace utility { class data_buffer; }

  class event {
  public:
    event();
    event(const char* event_id, float pass_prob = 1);
    event(event&& other);
    event& operator=(event&& other);
    virtual ~event();

    virtual bool try_drop(float pass_prob, int drop_pass);

    virtual void serialize(utility::data_buffer& buffer) = 0;
  
  protected:
    float prg(int drop_pass) const;

  protected:
    std::string _event_id;
    float _pass_prob;
  };

  class ranking_response;

  //serializable ranking event
  class ranking_event : public event {
  public:
    ranking_event();
    ranking_event(ranking_event&& other);
    ranking_event& operator=(ranking_event&& other);

    virtual void serialize(utility::data_buffer& buffer) override;
  
  public:
    static ranking_event choose_rank(utility::data_buffer& oss, const char* event_id, const char* context,
      unsigned int flags, const ranking_response& resp, float pass_prob = 1);

  private:
    ranking_event(const char* event_id, float pass_prob, const std::string& body);

  private:
    std::string _body;
  };

  //serializable outcome event
  class outcome_event : public event {
  public:
    outcome_event();
    outcome_event(outcome_event&& other);
    outcome_event& operator=(outcome_event&& other);

    virtual void serialize(utility::data_buffer& buffer) override;

  public:
    static outcome_event report_action_taken(utility::data_buffer& oss, const char* event_id, float pass_prob = 1);

    static outcome_event report_outcome(utility::data_buffer& oss, const char* event_id, const char* outcome, float pass_prob = 1);
    static outcome_event report_outcome(utility::data_buffer& oss, const char* event_id, float outcome, float pass_prob = 1);

  private:
    outcome_event(const char* event_id, float pass_prob, const std::string& body);
    
  private:
    std::string _body;
  };
}
