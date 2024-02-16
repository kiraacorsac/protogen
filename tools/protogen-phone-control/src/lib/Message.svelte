<script lang="ts">
  import ProtogenConfirmationButton from "./ProtogenConfirmationButton.svelte";

  export let url;
  let message;
</script>

<div>
  <div>
    <input type="text" maxlength="20" bind:value={message} />
  </div>
  <ProtogenConfirmationButton
    path="telemetryMessage"
    title="Message"
    {url}
    value={message}
  />
</div>
