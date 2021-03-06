open Oni_Model;
open Oni_IntegrationTestLib;

let keybindings = Some({|
invalid json
|});

runTest(
  ~keybindings,
  ~name="KeybindingsInvalidJson",
  (_dispatch, wait, _) => {
    wait(~name="Initial mode is normal", (state: State.t) =>
      Feature_Vim.mode(state.vim) |> Vim.Mode.isNormal
    );

    let getErrorNotificationCount = (state: State.t) => {
      let notifications: list(Feature_Notification.notification) =
        state.notifications;
      notifications
      |> List.filter((n: Feature_Notification.notification) =>
           n.kind == Feature_Notification.Error
         )
      |> List.length;
    };

    wait(~name="Get error message for invalid keybinding", (state: State.t) =>
      getErrorNotificationCount(state) > 0
    );
  },
);
